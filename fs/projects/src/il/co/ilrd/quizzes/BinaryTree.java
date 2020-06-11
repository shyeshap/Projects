package il.co.ilrd.quizzes;

import java.util.AbstractQueue;
import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.ArrayBlockingQueue;

public class BinaryTree {
	Node root;

	// Constructors 
	BinaryTree(int key) 
	{ 
		root = new Node(key); 
	} 

	BinaryTree() 
	{ 
		root = null; 
	} 

	private int height(Node root) {
		if (root == null) {
			return 0;
		}

		return 1 + Math.max(height(root.left), height(root.right));
	}

	private Node addRecursive(Node current, int value) {
		if (current == null) {
			return new Node(value);
		}

		if (value < current.data) {
			current.left = addRecursive(current.left, value);
		} else if (value > current.data) {
			current.right = addRecursive(current.right, value);
		} else {
			// value already exists
			return current;
		}

		return current;
	}

	public void add(int value) {
		root = addRecursive(root, value);
	}

	class Node 
	{ 
		int data; 
		Node left, right; 

		public Node(int item) 
		{ 
			data = item; 
			left = right = null; 
		} 
	}

	int hight(Node root) {
		return 0;
	}

	void printLevel(Node root, int level) {

	}

	/*	static void printLevelOrder(Node root) {
		if (root == null ) {
			return;
		}


		System.out.println(root.data);

		printLevelOrder(root.left);
		printLevelOrder(root.right);
		System.out.println("\n");

		return;
	}
	 */
	static void printLevelOrder(Node root) {
		Queue<Node> q = new LinkedList<Node>();
		Node current;

		q.add(root);

		while (!q.isEmpty()) {
			int cnt = q.size();
			
			while (cnt > 0) {
				
				current = q.peek();
				System.out.print(current.data + " ");
				q.remove();

				if (current.left != null) {
					q.add(current.left);
				}
				
				if (current.right != null) {
					q.add(current.right);
				}
				
				--cnt;
				
			}
			System.out.println();
		}
	}




	public static void main(String[] args) {
		BinaryTree bt = new BinaryTree(4);
		bt.add(2);
		bt.add(1);
		bt.add(6);
		bt.add(3);
		bt.add(5);
		bt.add(7);

		printLevelOrder(bt.root);
	}
	

}
