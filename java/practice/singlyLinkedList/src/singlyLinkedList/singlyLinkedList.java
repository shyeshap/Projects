package singlyLinkedList;

public class singlyLinkedList {
	private node head = new node(null, null);
	
	public void pushFront(Object data) {
		node newNode = new node(data, head);
		head = newNode;
	}
	
	public listIterator begin() {
		listIterator itr = new listIteratorImp();
		
		return itr;
	}
	
	public Boolean isEmpty() {
		 return !begin().hasNext();
	}
	
	public listIterator find(Object data) {
		listIterator itr = begin();
		
		while (itr.hasNext() || (data.equals(itr.next()))) {
		}
		
		return itr;
	}
	
	public long size() {
		listIterator itr = begin();
		long counter = 0L;
		
		while (itr.hasNext()) {
			++counter;
			itr.next();
		}
		
		return counter;
	}
	
	public Object popFront(){
		Object data = head.getData();
		head = head.getNextNode();
		
		return data;
	}

	private static class node {
		private Object data;
		private node nextNode;
			
		public node(Object data, node nextNode) {
			this.data = data;
			this.nextNode = nextNode;
		}

		public Object getData() {
			return data;
		}
		
		public node getNextNode() {
			return nextNode;
		}
	}
	
	private class listIteratorImp implements listIterator {
		node current;
		
		public listIteratorImp() {
			current = head;
		}
		
		@Override
		public Object next() {
			Object data = current.getData();
			current = current.getNextNode();
			
			return data;
		}
	
		@Override
		public Boolean hasNext() {
			
			return (current.getNextNode() != null);
		}
	
	}
}







