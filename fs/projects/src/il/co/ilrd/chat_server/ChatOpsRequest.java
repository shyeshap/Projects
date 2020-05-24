package il.co.ilrd.chat_server;

import java.nio.channels.SocketChannel;

import il.co.ilrd.chat_server.Msg;

public enum ChatOpsRequest {
	LOGIN {
		@Override
		public Request handleMsg(Request msg,  SocketChannel clientSocket) {
			//
		}
	},
	CREATE_GROUP {
		@Override
		public void handleMsg(Request msg,  SocketChannel clientSocket) {
		}
	},
	JOIN_GROUP {
		@Override
		public void handleMsg(Request msg,  SocketChannel clientSocket) {
		}
	},
	LEAVE_GROUP {
		@Override
		public void handleMsg(Request msg,  SocketChannel clientSocket) {
		}
	},
	SEND_MSG {
		@Override
		public void handleMsg(Request msg,  SocketChannel clientSocket) {
		}
	},

	LOGOUT {
		@Override
		public void handleMsg(Request msg,  SocketChannel clientSocket) {
			
		}
	};

	public abstract void handleMsg(Request msg,  SocketChannel clientSocket);
	
}
