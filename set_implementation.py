class set_impl:
    def __init__(self):
        self.collection = []
        self.menu()

    def create_set(self):
        size = int(input("Enter the number of elements: "))
        s = set()
        for i in range(size):
            s.add(int(input("Enter element {}: ".format(i+1))))

        return s
    def menu(self):
        while True:
            print("\n1. Create set\n2. Add element\n3. Remove element\n4. Contains element\n5. Display elements\n6. Intersection\n7. Union\n8. Difference\n9. Check Subset")
            print("Set count: {}".format(self.size()))
            choice = int(input("Enter your choice: "))

            if choice == 1:
                s = self.create_set()
                self.collection.append(s)

            elif choice == 2:
                set_no = int(input("Set number: "))
                self.collection[set_no - 1].add(int(input("Enter the element to add: ")))

            elif choice == 3:
                set_no = int(input("Set number: "))
                self.collection[set_no - 1].remove(int(input("Enter the element to remove: ")))

            elif choice == 4:
                set_no = int(input("Set number: "))
                print("Contains?:", int(input("Enter the element to check: ")) in self.collection[set_no - 1])

            elif choice == 5:
                set_no = int(input("Set number: "))
                print(self.collection[set_no - 1])

            elif choice == 6:
                if self.size() < 2:
                    print("Create atleast two sets!")
                    continue

                first_set = int(input("First set number: "))
                second_set = int(input("Second set number: "))
                print(self.collection[first_set - 1].intersection(self.collection[second_set - 1]))

            elif choice == 7:
                if self.size() < 2:
                    print("Create atleast two sets!")
                    continue

                first_set = int(input("First set number: "))
                second_set = int(input("Second set number: "))
                print(self.collection[first_set - 1].union(self.collection[second_set - 1]))

            elif choice == 8:
                if self.size() < 2:
                    print("Create atleast two sets!")
                    continue

                first_set = int(input("First set number: "))
                second_set = int(input("Second set number: "))
                print(self.collection[first_set - 1].difference(self.collection[second_set - 1]))

            elif choice == 9:
                if self.size() < 2:
                    print("Create atleast two sets!")
                    continue

                first_set = int(input("First set number: "))
                second_set = int(input("Second set number: "))
                print("Is Subset?", self.collection[first_set - 1].issubset(self.collection[second_set - 1]))

            else:
                break

    def size(self):
        return len(self.collection)

def main():
    s = set_impl()

if __name__ == "__main__":
    main()
