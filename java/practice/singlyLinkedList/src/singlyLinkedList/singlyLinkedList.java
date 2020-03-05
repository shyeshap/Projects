package singlyLinkedList;

public class singlyLinkedList {
	private node head = new node(null, null);
	
	/**
	 * Push new data to front of list.
	 * @param data: Object
	 * 
	 */
	public void pushFront(Object data) {
		node newNode = new node(data, head);
		head = newNode;
	}
	
	/**
	 * Get new beginning iterator.
	 * @return listIterator of the beginning of list
	 */
	public listIterator begin() {
		listIterator itr = new listIteratorImp();
		
		return itr;
	}
	
	/**
	 * Checks if list is empty
	 * @return true if empty and false if not
	 */
	public Boolean isEmpty() {
		 return !begin().hasNext();
	}
	
	/**
	 * Finds Object data in list 
	 * @param Object data
	 * @return listIterator of the correct location
	 */
	public listIterator find(Object data) {
		listIterator itr = begin();
		listIterator prevItr = begin();
		
		while (itr.hasNext()) {
			if (data.equals(itr.next())){
				
				return prevItr;
			}
				prevItr.next();
		}
		
		return prevItr;
	}
	
	/**
	 * 
	 * @return
	 */
	public long size() {
		listIterator itr = begin();
		long counter = 0L;
		
		while (itr.hasNext()) {
			++counter;
			itr.next();
		}
		
		return counter;
	}
	
	/**
	 * 
	 * @return
	 */
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







