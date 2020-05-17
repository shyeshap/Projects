package il.co.ilrd.chat_server;

import java.util.List;

public interface Peer {
	public void sendMessage(String senderName, Integer groupID, UsrProperties prop, String message);
	public void sendAddToGRoup(boolean status);
	public void sendNewGroupMember(Integer groupID, Integer newUsrID);
	public void sendLogin(Integer userID, List<Integer> groupID);
	public void sendCreateGroup(Integer groupID, String groupName);
	public void sendLeaveGroup(boolean status);
	public void sendGroupMemberLeaft(Integer groupID, Integer newUsrID);

}
