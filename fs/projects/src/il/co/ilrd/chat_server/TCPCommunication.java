package il.co.ilrd.chat_server;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.nio.ByteBuffer;
import java.nio.channels.*;
import java.util.Iterator;
import java.util.Set;

import il.co.ilrd.chat_msg.*;

public class TCPCommunication implements Communication {

	public ChatServer server;
	private int port = 22222;
	private Selector selector;
	private ServerSocketChannel serverChannel;
	private ServerSocket serverSocket;
	private SocketChannel channel;

	public TCPCommunication(ChatServer server) {
		this.server = server;
	}

	{
		try {
			selector = Selector.open();
			serverChannel = ServerSocketChannel.open();
			serverSocket =  serverChannel.socket();
			serverSocket.bind(new InetSocketAddress("localhost", port));
			serverChannel.configureBlocking(false);
			serverChannel.register(selector, SelectionKey.OP_ACCEPT);
		} catch (IOException e) {
			System.err.println(e.getMessage());
			e.printStackTrace();
		}
	}

	public static void main(String[] args) {
		new Thread (() -> {new TCPCommunication(new ChatServerHub()).Init(); }).start();
	}

	@Override
	public void Init() {
		while(true) {

			try {
				selector.select();
			} catch (IOException e) {
				e.printStackTrace();
			}

			Iterator<SelectionKey> keyIterator = selector.selectedKeys().iterator();

			while(keyIterator.hasNext()) {
				SelectionKey currentKey = keyIterator.next();
				if (currentKey.isAcceptable()) {
					ServerSocketChannel server = (ServerSocketChannel) currentKey.channel();
					SocketChannel client;
					try {
						client = server.accept();
						client.configureBlocking(false);
						client.register(selector, SelectionKey.OP_READ);
					} catch (IOException e) {
						e.printStackTrace();
					}
				}
				else if(currentKey.isReadable()) {
					channel = (SocketChannel) currentKey.channel();
					ByteBuffer bb = ByteBuffer.allocate(2048);
					Request request; 
					try {
						if(-1 == channel.read(bb)) {
							currentKey.cancel(); 
							keyIterator.remove(); 
							continue;
						}
						ObjectInputStream ois = new ObjectInputStream(new ByteArrayInputStream(bb.array()));
						request = (Request) ois.readObject();
						request.getOpId().handleMsg(request, channel, this);
					} catch (IOException | ClassCastException | ClassNotFoundException e) {
						currentKey.cancel();
						keyIterator.remove();
						continue;
					}
				}
				keyIterator.remove(); 
			}
		}
	}

	class SocketPeer implements Peer {
		private SocketChannel clientSocket = null;

		public SocketPeer(SocketChannel clientSocket) {
			this.clientSocket = clientSocket;
		}

		@Override
		public void responseMessage(int msgID, int userID, String userName, String groupName, UsrProperties prop,
				String message, Status status) {
			send(new ResponseSend(msgID, userID, groupName, message, userName, prop, status));
		}

		@Override
		public void responseJoinGroup(int msgID, int userID, String userName, String groupName, Status status) {
			send(new ResponseJoinGroup(msgID, userID, groupName, userName, status));
		}

		@Override
		public void responseLogin(int msgID, int userID, Set<String> groupNames, Status status) {
			send(new ResponseLogin(msgID, userID, groupNames, status));
		}

		@Override
		public void responseCreateGroup(int msgID, String groupName, Status status) {
			send(new ResponseCreateGroup(msgID, groupName, status));	
		}

		@Override
		public void responseLeaveGroup(int msgID, int userID, String userName, String groupName, Status status) {
			send(new ResponseLeaveGroup(msgID, userID, groupName, userName, status));		
		}

		private void send(Response reply) {
			ByteArrayOutputStream bos = new ByteArrayOutputStream();
			ObjectOutputStream out;
			try {
				out = new ObjectOutputStream(bos);
				out.writeObject(reply);
				out.flush();
				ByteBuffer bb = ByteBuffer.wrap(bos.toByteArray());
				clientSocket.write(bb);
			} catch (IOException e) {
				try {
					clientSocket.close();
				} catch (IOException e1) {
					e1.printStackTrace();
				}
			}
		}
	}
}