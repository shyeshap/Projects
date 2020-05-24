package il.co.ilrd.chat_server;

import java.nio.channels.SocketChannel;

import il.co.ilrd.chat_server.Msg;

public enum ChatOpsResponse {
	LOGIN {
		@Override
		public void handleMsg(Response msg,  SocketChannel clientSocket, TCPCommunication commun) {
		}
	},
	CREATE_GROUP {
		@Override
		public void handleMsg(Response msg,  SocketChannel clientSocket, TCPCommunication commun) {
		}
	},
	JOIN_GROUP {
		@Override
		public void handleMsg(Response msg,  SocketChannel clientSocket, TCPCommunication commun) {
		}
	},
	LEAVE_GROUP {
		@Override
		public void handleMsg(Response msg,  SocketChannel clientSocket, TCPCommunication commun) {
		}
	},
	SEND_MSG {
		@Override
		public void handleMsg(Response msg,  SocketChannel clientSocket, TCPCommunication commun) {
		}
	},

	LOGOUT {
		@Override
		public void handleMsg(Response msg,  SocketChannel clientSocket, TCPCommunication commun) {
			
		}
	};

	public abstract void handleMsg(Response msg,  SocketChannel clientSocket, TCPCommunication commun);
	
}
