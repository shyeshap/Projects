package il.co.ilrd.chat_server;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.Arrays;
import java.util.Iterator;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class TCPCommunication implements Communication {
	
	private ChatServer server;
	private static int portNum = 11111;
	private static String host = "localhost";
	
	public TCPCommunication(ChatServer server) {
		this.server = server;
	}
	
	public static void listen() throws IOException {
		Selector selector;
		selector = Selector.open();
		ServerSocketChannel serverSocket = ServerSocketChannel.open();
		InetSocketAddress socketAddress = new InetSocketAddress(host, portNum);
		serverSocket.bind(socketAddress);
		serverSocket.configureBlocking(false);
		int ops = serverSocket.validOps();
		SelectionKey key = serverSocket.register(selector, ops);
		
		while (true) {
			System.out.println("Waiting for new connection...");
			selector.select();
			Set<SelectionKey> keys = selector.selectedKeys();
			Iterator<SelectionKey> keyIterator = keys.iterator();
			
			while (keyIterator.hasNext()) {
				SelectionKey myKey = keyIterator.next();

				if (myKey.isAcceptable()) {
					SocketChannel clientSocket = serverSocket.accept();
					clientSocket.configureBlocking(false);
					clientSocket.register(selector, SelectionKey.OP_READ);
					System.out.println("Connection Accepted: " + clientSocket.getLocalAddress());
				} else if (myKey.isReadable()) {
					
					SocketChannel clientSocket = (SocketChannel) myKey.channel();
					ByteBuffer buff = ByteBuffer.allocate(256);
					clientSocket.read(buff);
					String msg = new String(buff.array()).trim();
 
					System.out.println("Message received: " + msg);
					String op = msg.substring(0,msg.indexOf('['));
					System.out.println(op);
					System.out.println(msg.substring(msg.indexOf('[')));
					ChatOps.valueOf(op).parse(msg.substring(msg.indexOf('[')));
					
					if (msg.equals("Crunchify")) {
						clientSocket.close();
						System.out.println("It's time to close connection as we got last company name");
						System.out.println("\nServer will keep running. Try running client again to establish new connection");
					}				
				}
			}
		}
	}
	
	public static void main(String[] args) throws IOException {
		listen();
	}
	
	enum ChatOps{
		LOG_IN 			(1) {
			@Override
			public void parse(String str) {
				String[] arr = str.split("\\[|]");
				for (String i : arr) {
					System.out.println(i);
				}
			}
		},
		CREATE_GROUP 	(2) {
			@Override
			public void parse(String str) {
				// TODO Auto-generated method stub
				
			}
		},
		JOIN_GROUP 		(3) {
			@Override
			public void parse(String str) {
				// TODO Auto-generated method stub
				
			}
		},
		LEAVE_GROUP 	(4) {
			@Override
			public void parse(String str) {
				// TODO Auto-generated method stub
				
			}
		},
		SEND_MSG		(5) {
			@Override
			public void parse(String str) {
				// TODO Auto-generated method stub
				
			}
		};
		
		int opNum;
		
		private ChatOps(int opNum) {
			this.opNum = opNum;
		}
		
		public abstract void parse(String str);
		
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
	
	class SocketPeer implements Peer {
		private Socket clientSocket = null;

		public SocketPeer(Socket clientSocket) {
			this.clientSocket = clientSocket;
		}
		
		@Override
		public void sendMessage(String senderName, int groupID, UsrProperties prop, String message) {
			// TODO Auto-generated method stub	
		}

		@Override
		public void sendAddToGRoup(int status) {}

		@Override
		public void sendNewGroupMember(int newUsrID) {}
		
		@Override
		public void sendLogin(int userID, int... groupID) {}
		
		@Override
		public void sendCreateGroup(int groupID, int groupName) {}
		
		@Override
		public void sendLeaveGroup(int status) {}

	}
}
