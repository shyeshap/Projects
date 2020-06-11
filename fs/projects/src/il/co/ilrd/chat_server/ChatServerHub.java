package il.co.ilrd.chat_server;

import java.awt.Color;
import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Random;
import java.util.Set;
import java.util.TreeSet;

public class ChatServerHub implements ChatServer{

	private Map<Integer, User> users = new HashMap<>();
	private Map<String, Group> groups = new HashMap<>();

	@Override
	public void logIn(int msgID, String email, String name, Peer peer) {
		User user;
<<<<<<< HEAD
		if((user = userEmailPresent(email, name)) != null) {
			user.peer = peer;
		}
		else { 
			user = new User(name, email, peer);
			users.put(user.getID(), user);
		}
		peer.responseLogin(msgID, user.getID(), user.groupNames, Status.SUCCESS);
	}

	private User userEmailPresent(String email, String name) {
		for(Entry<Integer, User> entry : users.entrySet()) {
			if(entry.getValue().email.equalsIgnoreCase(email)) {
				return entry.getValue();
			}
		}
		return null;
	}

	@Override
	public void createNewGroup(int msgID, Integer userID, String groupName) {
		User user = users.get(userID);
		Status status;
		if(user == null) { 
			return; 
		}
		else if(groups.containsKey(groupName)) { 
			status = Status.GROUP_ALREADY_EXISTS;
		}
		else {
			Group group = new Group(groupName);
			groups.put(groupName, group);
			user.addGroup(group);
			group.addUser(user);
			status = Status.SUCCESS;
		}
		user.peer.responseCreateGroup(msgID, groupName, status);
	}

	@Override
	public void joinGroup(int msgID, Integer userID, String groupName) {
		Status status;
		User user = users.get(userID);
		Group group = groups.get(groupName);
		if(user == null) { 
			return; 
		}
		else if(group == null) { 
			status = Status.GROUP_NOT_FOUND; 
		}
		else if(user.groupNames.contains(groupName)) { 
			status = Status.ALREADY_IN_GROUP; 
		}
		else {
			status = Status.SUCCESS;
			for(Integer member : group.users.keySet()) { 
				users.get(member).peer.responseJoinGroup(msgID, userID, user.name, groupName, status); 
			}
			user.addGroup(group);
			group.addUser(user);
		}
		user.peer.responseJoinGroup(msgID, userID, user.name, groupName, status);
	}

	@Override
=======
		
		if (peer == null) { return; }
		
		if ((user = findUserByEmail(email, name)) != null) {
			user.peer = peer;
		}
		
		else { 
			if ((user = User.getInstance(name, email, peer)) != null);
			users.put(user.getID(), user);
		}
		
		peer.responseLogin(msgID, user.getID(), user.groupNames, Status.SUCCESS);
	}

	private User findUserByEmail(String email, String name) {
		for (Entry<Integer, User> entry : users.entrySet()) {
			if(entry.getValue().email.equals(email)) {
				return entry.getValue();
			}
		}
		
		return null;
	}

	@Override
	public void createNewGroup(int msgID, Integer userID, String groupName) {
		User user = users.get(userID);
		Status status;
		
		if (user == null) { 
			return; 
		} else if (users.containsKey(userID)) {
			status = Status.CLIENT_NOT_FOUND;
		} else if (groups.containsKey(groupName)) { 
			status = Status.GROUP_ALREADY_EXISTS;
		} else {
			Group group;
			if ((group = Group.getInstance(groupName)) != null) {
				groups.put(groupName, group);
				user.addGroup(group);
				group.addMember(user);
				status = Status.SUCCESS;
			}
			status = Status.BAD_INPUT;
		}
		user.peer.responseCreateGroup(msgID, groupName, status);
	}

	@Override
	public void joinGroup(int msgID, Integer userID, String groupName) {
		Status status;
		User user = users.get(userID);
		Group group = groups.get(groupName);
		
		if (user == null) { 
			return; 
		} else if (users.containsKey(userID)) {
			status = Status.CLIENT_NOT_FOUND;
		} else if (group == null) { 
			status = Status.GROUP_NOT_FOUND; 
		} else if (user.groupNames.contains(groupName)) { 
			status = Status.ALREADY_IN_GROUP; 
		} else {
			status = Status.SUCCESS;
			for(Integer member : group.groupMembers.keySet()) { 
				users.get(member).peer.responseJoinGroup(msgID, userID, user.name, groupName, status); 
			}
			user.addGroup(group);
			group.addMember(user);
		}
		
		user.peer.responseJoinGroup(msgID, userID, user.name, groupName, status);
	}

	@Override
>>>>>>> d47918d3f7a133ac41ab8c1ddd184079bc741119
	public void leaveGroup(int msgID, Integer userID, String groupName) {
		Status status;
		User user = users.get(userID);
		Group group = groups.get(groupName);

<<<<<<< HEAD
		if(user == null) { 
			return; 
		}
		else if(group == null) { 
			status = Status.GROUP_NOT_FOUND; 
		}
		else if(group.users.remove(userID)== null) { 
			status = Status.NOT_IN_GROUP; 
		}
		else {
			status = Status.SUCCESS;
			user.groupNames.remove(groupName);
			for(Integer member : group.users.keySet()) { 
=======
		if (user == null) { 
			return; 
		} else if (users.containsKey(userID)) {
			status = Status.CLIENT_NOT_FOUND;
		} else if (group == null) { 
			status = Status.GROUP_NOT_FOUND; 
		} else if ((group.removeMember(userID))) { 
			status = Status.NOT_IN_GROUP; 
		} else {
			status = Status.SUCCESS;
			user.leaveGroup(groupName);
			for(Integer member : group.groupMembers.keySet()) { 
>>>>>>> d47918d3f7a133ac41ab8c1ddd184079bc741119
				users.get(member).peer.responseLeaveGroup(msgID, userID, user.name, groupName, status);
			}
		}
		user.peer.responseLeaveGroup(msgID, userID, user.name, groupName, status);
	}

	@Override
	public void sendMsg(int msgID, Integer userID, String groupName, String msg) {
		Status status;
		User user = users.get(userID);
		Group group = groups.get(groupName);
<<<<<<< HEAD
		if(user == null) { 
			return; 
		}
		else if(group == null) { 
			status = Status.GROUP_NOT_FOUND; 
		}
		else if(!user.groupNames.contains(groupName)) { 
			status = Status.NOT_IN_GROUP; 
		}
		else{
			status = Status.SUCCESS;
			for(Entry<Integer, UsrProperties> member : group.users.entrySet()) { 
=======
		
		if (user == null) { 
			return; 
		} else if (users.containsKey(userID)) {
			status = Status.CLIENT_NOT_FOUND;
		} else if (group == null) { 
			status = Status.GROUP_NOT_FOUND; 
		} else if (!user.groupNames.contains(groupName)) { 
			status = Status.NOT_IN_GROUP; 
		} else{
			status = Status.SUCCESS;
			for(Entry<Integer, UsrProperties> member : group.groupMembers.entrySet()) { 
>>>>>>> d47918d3f7a133ac41ab8c1ddd184079bc741119
				users.get(member.getKey()).peer.responseMessage(msgID, userID, user.name, groupName, member.getValue() , msg, status);
			}
			return;
		}
		System.out.println(status + "status");
		user.peer.responseMessage(msgID, userID, user.name, groupName, null , msg, status);

	}

	private static class User {
		private String name;
		private String email;
		private int id;
		private Peer peer;
		private Set<String> groupNames = new TreeSet<>();
		private static int counter;

		private User(String name, String email, Peer peer) {
			this.name = name;
			this.email = email;
			this.id = ++counter;
			this.peer = peer;
		}	

<<<<<<< HEAD
		private int getID() { return id; }

		private void addGroup(Group group) { groupNames.add(group.getName()); }
	}

	private static class Group {
		private Map<Integer, UsrProperties> users = new HashMap<>();
=======
		private static User getInstance(String name, String email, Peer peer) {
			if (name == null || email == null || peer == null) { return null; }
			return new User(name, email, peer);
		}
		
		private int getID() { return id; }
		private void addGroup(Group group) { groupNames.add(group.getName()); }
		private boolean leaveGroup(String groupName) { 
			return groupNames.remove(groupName); 
		}
	}

	private static class Group {
		private Map<Integer, UsrProperties> groupMembers = new HashMap<>();
>>>>>>> d47918d3f7a133ac41ab8c1ddd184079bc741119
		private String name;

		private Group(String name) {
			this.name = name;
		}
<<<<<<< HEAD

		private String getName() { return name; }

		private void addUser(User user) { users.put(user.getID(), new ColorUsrProperties()); }
=======
		
		private static Group getInstance(String name) {
			if (name == null) {
				return null;
			}
			
			return new Group(name); 
		}

		private String getName() { return name; }
	
		private void addMember(User user) { 
			groupMembers.put(user.getID(), new ColorUsrProperties()); 
		}
		
		private boolean removeMember(Integer userId) { 
			return (groupMembers.remove(userId) != null); 
		}
>>>>>>> d47918d3f7a133ac41ab8c1ddd184079bc741119
	}

	private static class ColorUsrProperties implements UsrProperties{
		/**
		 * 
		 */
		private static final long serialVersionUID = 2707209719101696203L;
		Color color;

		private ColorUsrProperties() {
<<<<<<< HEAD
			Random rand = new Random();
			color = new Color(rand.nextFloat(), rand.nextFloat(), rand.nextFloat());
=======
			color = getRandomColor();
		}
		
		private Color getRandomColor() {
			Random rand = new Random();
			return new Color(rand.nextFloat(), rand.nextFloat(), rand.nextFloat());
>>>>>>> d47918d3f7a133ac41ab8c1ddd184079bc741119
		}
		public Color getColor() { return color; }
	}
}