class MyLinkedList {
    private:
        struct Node {
            int value;
            Node* next;
            Node(int val) : value(val), next(nullptr) {}
        };
        Node* head;
    
    public:
    
        int get(int index) {
            Node* cur = head;
            for(int i=0;i<index && cur;i++) {
                cur = cur->next;
            }
            if(cur) return cur->value;
            return -1;
        }
        
        void addAtHead(int val) {
            Node* newNode = new Node(val);
            newNode->next = head;
            head = newNode;
        }
    
        void addAtTail(int val) {
            Node* newNode = new Node(val);
            if(!head) {
                head = newNode;
                return;
            }
            Node* cur = head;
            while(cur->next) {
                cur = cur->next;
            }
            cur->next = newNode;
        }
    
        void addAtIndex(int index, int val) {
            if(index == 0) {
                addAtHead(val);
                return;
            }
            Node* cur = head;
            for(int i=0;i<index-1 && cur;i++) {
                cur = cur->next;
            }
            if(!cur) return;
            Node* newNode = new Node(val);
            newNode->next = cur->next;
            cur->next = newNode;

        }
        void deleteAtIndex(int index) {
            if(index == 0) {
                if(head) {
                    Node* temp = head;
                    head = head->next;
                    delete temp;
                }
                return;
            }
            Node* cur = head;
            for(int i=0;i<index-1 && cur;i++) {
                cur = cur->next;
            }
            if(!cur || !cur->next) return;
            Node* temp = cur->next;
            cur->next = cur->next->next;
            delete temp;

        }
    };
    