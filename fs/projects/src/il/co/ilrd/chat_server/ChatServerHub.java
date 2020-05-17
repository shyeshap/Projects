package il.co.ilrd.chat_server;

import java.awt.Color;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Map;

import il.co.ilrd.collection.HashMap;

public class ChatServerHub implements ChatServer{
	
	private Map<Integer, User> users = new HashMap<>();
	private Map<Integer, Group> groups = new HashMap<>();
	private static int currUsrID = 0;
	private static int currGroupID = 0;
	
	@Override
	public void logIn(String email, String name, Peer p) {
		System.out.println("login");
		Collection<User> usersCollection = users.values();
		User user = null;
				
		for (User u : usersCollection) {
			if (u.email == email) {
				user = u;
			}
		}
		
		if (user == null) {
			user = new User(name, email, p);
			users.put(user.id, user);
		}
		
		p.sendLogin(user.id, user.groups);
	}

	@Override
	public void createNewGroup(Integer userId, String groupName) {
		User user = users.get(userId);
		//if (user != null)
		Group newGroup = new Group(groupName, user.id);
		groups.put(newGroup.id, newGroup);
		
		user.peer.sendCreateGroup(newGroup.id, groupName);
	}

	@Override
	public void joinGroup(Integer userId, Integer groupId) {
		User user = users.get(userId);
		Group group = groups.get(groupId);
		boolean status = false;
		
		if (user != null && group != null && !group.users.containsKey(userId)) {
			status = true;
			group.users.put(user.id, new ColourUsrProperties());
			for (Integer member : group.users.keySet()) {
				users.get(member).peer.sendNewGroupMember(group.id, user.id);
			}
		}

		user.peer.sendAddToGRoup(status);
	}

	@Override
	public void leaveGroup(Integer userId, Integer groupId) {
		User user = users.get(userId);
		Group group = groups.get(groupId);
		boolean status = false;
		
		if (user != null && group != null && group.users.containsKey(userId)) {
			status = true;
			group.users.put(user.id, new ColourUsrProperties());
			for (Integer member : group.users.keySet()) {
				users.get(member).peer.sendGroupMemberLeaft(group.id, user.id);
			}
		}

		user.peer.sendLeaveGroup(status);
		
	}

	@Override
	public void sendMsg(Integer userId, Integer groupId, String msg) {
		User user = users.get(userId);
		Group group = groups.get(groupId);
		
		//if (user != null && group != null && group.users.containsKey(userId))
		for (Integer member : group.users.keySet()) {
			users.get(member).peer.sendMessage(user.name, groupId, group.users.get(userId), msg);
		}
		
	}
	
	private static class User {
		private String name;
		private String email;
		private Integer id;
		private Peer peer;
		private static int counter;
		private ArrayList<Integer> groups;
		
		public User(String name, String email, Peer peer) {
			this.name = name;
			this.email = email;
			this.id = ++counter;
			this.peer = peer;
			groups = new ArrayList<>();
		}	
		
	}
	
	private static class ColourUsrProperties implements UsrProperties{
		Color color;
		
	}

	private static class Group {
		private Map<Integer, UsrProperties> users = new HashMap<>();
		private static int counter = 0;
		private Integer id = ++counter;
		private String name;
		
		private Group(String name, Integer ownerId) {
			this.name = name;
			users.put(ownerId, new ColourUsrProperties());
		}
	}
}
