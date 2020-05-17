package il.co.ilrd.chat_server;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Set;
import java.util.StringTokenizer;

public class TCPCommunication implements Communication {
	private ChatServer server;
	private int portNum;
	private String host = "localhost";
	private boolean flag = true;
	private Selector selector;
	
	public TCPCommunication(ChatServer server, int portNum) {
		this.server = server;
		this.portNum = portNum;
	}
	
	public void listen() throws IOException {
		selector = Selector.open();
		ServerSocketChannel serverSocket = ServerSocketChannel.open();
		InetSocketAddress socketAddress = new InetSocketAddress(host, portNum);
		serverSocket.bind(socketAddress);
		serverSocket.configureBlocking(false);
		int ops = serverSocket.validOps();
		serverSocket.register(selector, ops);
		
		while (flag) {
			System.out.println("Waiting for new connection...");
			selector.select();
			Set<SelectionKey> keys = selector.selectedKeys();
			Iterator<SelectionKey> keyIterator = keys.iterator();
			
			while (keyIterator.hasNext()) {
				SelectionKey selectionKey = keyIterator.next();
				
				if (selectionKey.isAcceptable()) {
					SocketChannel clientSocket = serverSocket.accept();
					if (clientSocket == null ) { continue; }
					clientSocket.configureBlocking(false);
					clientSocket.register(selector, SelectionKey.OP_READ);
					
				//	handleAccept(serverSocket, selectionKey);
					
				} else if (selectionKey.isReadable()) {
					SocketChannel clientSocket = (SocketChannel) selectionKey.channel();
					ByteBuffer buff = ByteBuffer.allocate(256);
					clientSocket.read(buff);
					String msg = new String(buff.array()).trim();
					StringTokenizer token = new StringTokenizer(msg, "[]");
					ChatOps.valueOf(token.nextToken()).parse(token, clientSocket, this);
					
				//	handleRead(serverSocket, selectionKey);
				}
				keyIterator.remove();
			}
		}
	}
	/*
	private void handleAccept(ServerSocketChannel socket, SelectionKey key) throws IOException {
		SocketChannel clientSocket = socket.accept();
		clientSocket.configureBlocking(false);
		clientSocket.register(this.selector, SelectionKey.OP_READ);
	}
	
	private void handleRead(ServerSocketChannel socket, SelectionKey key) throws IOException {
		SocketChannel clientSocket = (SocketChannel) key.channel();
		ByteBuffer buff = ByteBuffer.allocate(256);
		clientSocket.read(buff);
		String msg = new String(buff.array()).trim();
		StringTokenizer token = new StringTokenizer(msg, "[]");
		ChatOps.valueOf(token.nextToken()).parse(token, clientSocket, this);
	}
	*/
	
	public static void main(String[] args) throws IOException {
		TCPCommunication commun = new TCPCommunication(new ChatServerHub(), 11111);
		commun.listen();
	}
	
	enum ChatOps{
		LOG_IN 			(1) {
			@Override
			public void parse(StringTokenizer token,  SocketChannel clientSocket, TCPCommunication commun) {
				commun.server.logIn(token.nextToken(), token.nextToken(), new SocketPeer(clientSocket));
			}
		},
		CREATE_GROUP 	(2) {
			@Override
			public void parse(StringTokenizer token,  SocketChannel clientSocket, TCPCommunication commun) {
				commun.server.createNewGroup(Integer.parseInt(token.nextToken()), token.nextToken());
			}
		},
		JOIN_GROUP 		(3) {
			@Override
			public void parse(StringTokenizer token,  SocketChannel clientSocket, TCPCommunication commun) {
				commun.server.joinGroup(Integer.parseInt(token.nextToken()), Integer.parseInt(token.nextToken()));
			}
		},
		LEAVE_GROUP 	(4) {
			@Override
			public void parse(StringTokenizer token,  SocketChannel clientSocket, TCPCommunication commun) {
				commun.server.leaveGroup(Integer.parseInt(token.nextToken()), Integer.parseInt(token.nextToken()));
			}
		},
		SEND_MSG		(5) {
			@Override
			public void parse(StringTokenizer token,  SocketChannel clientSocket, TCPCommunication commun) {
				commun.server.sendMsg(Integer.parseInt(token.nextToken()), Integer.parseInt(token.nextToken()), token.nextToken());
			}
		},

		LOG_OUT			(6) {
			@Override
			public void parse(StringTokenizer token,  SocketChannel clientSocket, TCPCommunication commun) {
				try {
					clientSocket.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
				commun.flag = false;
				System.out.println("logged out");
			}
		};

		int opNum;
		
		private ChatOps(int opNum) {
			this.opNum = opNum;
		}
		
		public abstract void parse(StringTokenizer token,  SocketChannel clientSocket, TCPCommunication commun);
		
		public int getOpNum() { return opNum; }
		
		public static ChatOps getOp(int num) {
			for (ChatOps op : ChatOps.values()) {
	            if (op.getOpNum() == num) {
	                return op;
	            }
	        }
	        return null;
		}
	}
	
	@Override
	public void Init() {
		
		
	}
	
	private static class SocketPeer implements Peer {
		private SocketChannel clientSocket;

		public SocketPeer(SocketChannel clientSocket) {
			this.clientSocket = clientSocket;
		}
		
		@Override
		public void sendMessage(String senderName, Integer groupID, UsrProperties prop, String message) {
			
		}

		@Override
		public void sendAddToGRoup(boolean status) {}

		@Override
		public void sendNewGroupMember(Integer groupID, Integer newUsrID) {}
		
		@Override
		public void sendLogin(Integer userID, List<Integer> groups) {
			StringBuilder reply = new StringBuilder();
			reply.append("LOGIN[" + userID.toString() + "]");
			for (Integer i : groups) {
				reply.append("[");
				reply.append(i);
				reply.append("]");
			}
			
			System.out.println("sendLogin: " + reply);
			byte[] message = new String(reply).getBytes();
			ByteBuffer buffer = ByteBuffer.wrap(message);
			try {
				clientSocket.write(buffer);
			} catch (IOException e) {
				e.printStackTrace();
			}

		}
		
		@Override
		public void sendCreateGroup(Integer groupID, String groupName) {}
		
		@Override
		public void sendLeaveGroup(boolean status) {}
		
		@Override
		public void sendGroupMemberLeaft(Integer groupID, Integer newUsrID) {}

	}
}
