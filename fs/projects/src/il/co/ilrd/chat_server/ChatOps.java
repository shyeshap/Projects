package il.co.ilrd.chat_server;

import java.io.IOException;
import java.nio.channels.SocketChannel;

import il.co.ilrd.chat_msg.*;
import il.co.ilrd.chat_msg.RequestCreateGroup;
import il.co.ilrd.chat_msg.RequestLogin;
import il.co.ilrd.chat_msg.RequestSend;

public enum ChatOps {

	LOGIN {
		@Override
		public void handleMsg(Request msg,  SocketChannel clientSocket, TCPCommunication commun) {
			RequestLogin reply = (RequestLogin)msg;
			commun.server.logIn(reply.getMsgID(), reply.getEmail(), reply.getUserName(), commun. new SocketPeer(clientSocket));
		}
	},
	CREATE_GROUP {
		@Override
		public void handleMsg(Request msg,  SocketChannel clientSocket, TCPCommunication commun) {
			RequestCreateGroup reply = (RequestCreateGroup)msg;
			commun.server.createNewGroup(reply.getMsgID(), reply.getUserId(), reply.getGroupName());
		}
	},
	JOIN_GROUP {
		@Override
		public void handleMsg(Request msg,  SocketChannel clientSocket, TCPCommunication commun) {
			RequestJoinGroup reply = (RequestJoinGroup)msg;
			commun.server.joinGroup(reply.getMsgID(), reply.getUserId(), reply.getGroupName());
		}
	},
	LEAVE_GROUP {
		@Override
		public void handleMsg(Request msg,  SocketChannel clientSocket, TCPCommunication commun) {
			RequestLeaveGroup reply = (RequestLeaveGroup)msg;
			commun.server.leaveGroup(reply.getMsgID(), reply.getUserId(), reply.getGroupName());
		}
	},
	SEND_MSG {
		@Override
		public void handleMsg(Request msg,  SocketChannel clientSocket, TCPCommunication commun) {
			RequestSend reply = (RequestSend)msg;
			commun.server.sendMsg(reply.getMsgID(), reply.getUserId(), reply.getGroupName(), reply.getMsg());
		}
	},

	LOGOUT {
		@Override
		public void handleMsg(Request msg,  SocketChannel clientSocket, TCPCommunication commun) {
			//				RequestLogout reply = (RequestLogin)msg;
			//				commun.server.logIn(reply.getMsgID(), reply.getEmail(), reply.getUserName(), commun. new SocketPeer(clientSocket));
		}
	};

	public abstract void handleMsg(Request msg,  SocketChannel clientSocket, TCPCommunication commun);

}
