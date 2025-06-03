class Node:
    """
    A class representing a node in a singly linked list.
    """
    def __init__(self, data):
        self.data = data
        self.next = None


class SinglyLinkedList:
    """
    A class to manage a singly linked list.
    """
    def __init__(self):
        self.head = None

    def insert_at_end(self, data):
        new_node = Node(data)
        if not self.head:
            self.head = new_node
            return
        curr = self.head
        while curr.next:
            curr = curr.next
        curr.next = new_node

    def insert_at_beginning(self, data):
        new_node = Node(data)
        new_node.next = self.head
        self.head = new_node

    def insert_after_value(self, target, data):
        curr = self.head
        while curr:
            if curr.data == target:
                new_node = Node(data)
                new_node.next = curr.next
                curr.next = new_node
                return
            curr = curr.next
        raise ValueError(f"Value '{target}' not found.")

    def delete_value(self, target):
        if not self.head:
            raise ValueError("List is empty.")

        if self.head.data == target:
            self.head = self.head.next
            return

        curr = self.head
        while curr.next:
            if curr.next.data == target:
                curr.next = curr.next.next
                return
            curr = curr.next

        raise ValueError(f"Value '{target}' not found.")

    def traverse(self):
        elements = []
        curr = self.head
        while curr:
            elements.append(curr.data)
            curr = curr.next
        return elements

    def __str__(self):
        return " -> ".join(map(str, self.traverse())) + " -> None"


# === Main program with user interaction ===
def main():
    ll = SinglyLinkedList()

    while True:
        print("\n--- Singly Linked List Menu ---")
        print("1. Insert at beginning")
        print("2. Insert at end")
        print("3. Insert after value")
        print("4. Delete a value")
        print("5. Display list")
        print("6. Exit")
        choice = input("Enter your choice (1-6): ")

        try:
            if choice == '1':
                val = input("Enter value to insert at beginning: ")
                ll.insert_at_beginning(val)
            elif choice == '2':
                val = input("Enter value to insert at end: ")
                ll.insert_at_end(val)
            elif choice == '3':
                target = input("Enter the value after which to insert: ")
                val = input("Enter value to insert: ")
                ll.insert_after_value(target, val)
            elif choice == '4':
                val = input("Enter value to delete: ")
                ll.delete_value(val)
            elif choice == '5':
                print("Linked List:")
                print(ll)
            elif choice == '6':
                print("Exiting program.")
                break
            else:
                print("Invalid choice. Please enter a number between 1 and 6.")
        except ValueError as ve:
            print(f"Error: {ve}")

if __name__ == "__main__":
    main()
1
