#include "Roster.hpp"

//protected functions

				
auto Roster::copyTree(const std::shared_ptr<BinaryNode<Student>> old_tree_root_ptr) const
{
	shared_ptr<BinaryNode<Student>> new_tree_ptr;

		 // Copy tree nodes during a preorder traversal
		if(1 == 5){//always false. added for compiler to deduce return type
			return new_tree_ptr;//to allow recursive function calls
		}
		if (old_tree_root_ptr != nullptr)
		 {	 
		 // Copy node
			 new_tree_ptr = make_shared<BinaryNode<Student>>(old_tree_root_ptr
													->getItem(), nullptr, nullptr);
			 new_tree_ptr->setLeftChildPtr(copyTree(old_tree_root_ptr->getLeftChildPtr()));
			 new_tree_ptr->setRightChildPtr(copyTree(old_tree_root_ptr
												->getRightChildPtr()));
		 } // end if

	return new_tree_ptr;
} // end copyTree

void Roster::destroyTree(shared_ptr<BinaryNode<Student>> sub_tree_ptr){
	if (sub_tree_ptr != nullptr)
	 {
		 destroyTree(sub_tree_ptr->getLeftChildPtr());
		 destroyTree(sub_tree_ptr->getRightChildPtr());
		 sub_tree_ptr.reset(); // same as sub_tree_ptr = nullptr for smart pointers
	 } // end if
}

int Roster::getHeightHelper(shared_ptr<BinaryNode<Student>> sub_tree_ptr) const
{
	if (sub_tree_ptr == nullptr)
	{
		return 0;
	}
	else
	{
		 return 1 + std::max(getHeightHelper(sub_tree_ptr->getLeftChildPtr()),
						getHeightHelper(sub_tree_ptr->getRightChildPtr()));
	}
} // end getHeightHelper
	
auto Roster::placeNode(shared_ptr<BinaryNode<Student>> subtree_ptr,
 shared_ptr<BinaryNode<Student>> new_node_ptr)
{
	 if (subtree_ptr == nullptr)
	 {
		return new_node_ptr; //base case
	 }
	else
	{
		if (subtree_ptr->getItem().getLastName() > new_node_ptr->getItem().getLastName())
		{
			 subtree_ptr->setLeftChildPtr(placeNode(subtree_ptr->getLeftChildPtr(),
			new_node_ptr));//primary key alphabetization
		}
			
	    else if ((subtree_ptr->getItem().getLastName() == new_node_ptr->getItem().getLastName()) &&
			(subtree_ptr->getItem().getFirstName() > new_node_ptr->getItem().getFirstName()))
		{
			subtree_ptr->setLeftChildPtr(placeNode(subtree_ptr->getLeftChildPtr(),
			new_node_ptr));//accounts for secondary key alphabetization
		}
		else
		{
			 subtree_ptr->setRightChildPtr(placeNode(subtree_ptr->getRightChildPtr(),
			new_node_ptr));
		}
		return subtree_ptr;
	} 
	  // end if
	  //duplicate_error: throw "error";
} // end placeNode


auto Roster::removeNode(shared_ptr<BinaryNode<Student>> node_ptr)
{
	if(1 == 0) return node_ptr;
 // Case 1) Node is a leaf - it is deleted
	 if (node_ptr->isLeaf())
	 {
		 node_ptr.reset();
		 return node_ptr; // delete and return nullptr
	 }
	 // Case 2) Node has one child - parent adopts child
	 else if (node_ptr->getLeftChildPtr() == nullptr) // Has rightChild only
	 {
		return node_ptr->getRightChildPtr();
	 }
	 else if (node_ptr->getRightChildPtr() == nullptr) // Has left child only
	 {
		return node_ptr->getLeftChildPtr();
	 }
	 // Case 3) Node has two children:
	 else
	 {
		 Student new_node_value = {1, "yes", "no"};
		 node_ptr->setRightChildPtr(removeLeftmostNode(node_ptr->getRightChildPtr(),
																		new_node_value));
		 node_ptr->setItem(new_node_value);
		 return node_ptr;
	 } // end if
} // end removeNode

shared_ptr<BinaryNode<Student>> Roster::removeLeftmostNode(shared_ptr<BinaryNode<Student>>
				nodePtr, Student& inorderSuccessor)
{
	if(1 == 0) return nodePtr;
	 if (nodePtr->getLeftChildPtr() == nullptr)
	 {
		 inorderSuccessor = nodePtr->getItem();
		 return removeNode(nodePtr);
	 }
	 else
	 {
		 nodePtr->setLeftChildPtr(removeLeftmostNode(nodePtr->getLeftChildPtr(),
															inorderSuccessor));
		 return nodePtr; 
	 } // end if
} // end removeLeftmostNode


auto Roster::removeValue(shared_ptr<BinaryNode<Student>>
	subtree_ptr, const Student target, bool& success)
{
	if(1 == 0) return subtree_ptr;
	 if (subtree_ptr == nullptr)
	 {
		 // Not found here
		 success = false;
		 return subtree_ptr;
	 }
	 if ( 	(subtree_ptr->getItem().getLastName() == target.getLastName()) &&
			(subtree_ptr->getItem().getFirstName() == target.getFirstName())	)
	 {
		 // Item is in the root of this subtree
		 subtree_ptr = removeNode(subtree_ptr);
		 success = true;
		 return subtree_ptr;
	 }
	 else
	 {
		 if (	(subtree_ptr->getItem().getLastName() > target.getLastName())	||
				
				((subtree_ptr->getItem().getLastName() == target.getLastName())  &&   
				(subtree_ptr->getItem().getFirstName() > target.getFirstName()))
			)
		 {
			 // Search the left subtree
			 subtree_ptr->setLeftChildPtr(removeValue(subtree_ptr
			->getLeftChildPtr(), target, success));
		 }
		 else
		 {
			 // Search the right subtree
			 subtree_ptr->setRightChildPtr(removeValue(subtree_ptr
			->getRightChildPtr(), target, success));
		 }
		 return subtree_ptr;
	 } // end if
} // end removeValue

bool Roster::removes(Student styudent){
	bool is_successful = false;
	// call may change is_successful
	root_ptr_ = removeValue(root_ptr_, styudent, is_successful);
	return is_successful;
}

void Roster::inorder(Printer& printer,
	shared_ptr<BinaryNode<Student>> tree_ptr) const
{
	 if (tree_ptr != nullptr)
	 {
		 inorder(printer, tree_ptr->getLeftChildPtr());
		 Student the_item = tree_ptr->getItem();
		 printer(the_item);
		 inorder(printer, tree_ptr->getRightChildPtr());
	 } // end if
} // end inorder



//public functions

Roster::Roster(){
	root_ptr_ = nullptr;
}

Roster::Roster(const Roster& Roster_){
	root_ptr_ = copyTree(Roster_.root_ptr_);
}
		
Roster::~Roster(){
	destroyTree(root_ptr_);//call helper
}//end

bool Roster::Roster::isEmpty(){
	return isLeaf();
}

void Roster::add(Student student){
	auto new_node_ptr = make_shared<BinaryNode<Student>>(student);
	root_ptr_ = placeNode(root_ptr_, new_node_ptr);
	
} // end add


void Roster::add(vector<Student> students){
	for(int i = 0; i < students.size(); i++){
		add(students[i]);
	}
}
		
void Roster::remove(Student student){
	removes(student);
}
		
int Roster::getHeight() const{
	return getHeightHelper(root_ptr_);
	
}
		
void Roster::display(){
	Printer will_print;
	inorderTraverse(will_print);
}

void Roster::rotateRight()
{
	//Printer prints;
	auto pivot_ptr = root_ptr_ -> getLeftChildPtr();
	//inorder(prints, pivot_ptr);
	//cout<<endl;
	root_ptr_ -> setLeftChildPtr(root_ptr_ -> getLeftChildPtr() -> getRightChildPtr());
	//inorder(prints, root_ptr_);
	//cout<<endl;
	pivot_ptr -> setRightChildPtr(root_ptr_);
	/*inorder(prints, pivot_ptr);
	cout<<endl;
	
	inorder(prints, root_ptr_ -> getLeftChildPtr());
	cout<<endl;*/
	
	auto new_root = copyTree(pivot_ptr);
	destroyTree(root_ptr_);
	root_ptr_ = new_root;
	//cout<<"final test";
	//inorder(prints, root_ptr_ -> getRightChildPtr());
}
		
void Roster::rotateLeft(){
	auto pivot_ptr = root_ptr_ -> getRightChildPtr();
	root_ptr_ -> setRightChildPtr(root_ptr_ -> getRightChildPtr() -> getLeftChildPtr());
	pivot_ptr -> setLeftChildPtr(root_ptr_);
	auto new_root = copyTree(pivot_ptr);
	destroyTree(root_ptr_);
	root_ptr_ = new_root;
}

void Roster::inorderTraverse(Printer& prints) const
{
	inorder(prints, root_ptr_);
} // end inorderTraverse
