#ifndef ROSTER_HPP_
#define ROSTER_HPP_

#include "Printer.hpp"
#include "BinaryNode.hpp"

#include <vector>

using namespace std;

class Roster: public BinaryNode<Student *>{
	public:
		Roster();
		Roster(const Roster& Roster_);
		~Roster();
		bool isEmpty();
		void add(Student student);
		void add(vector<Student> students);
		void remove(Student student);
		int getHeight() const;
		void display();
		void rotateLeft();
		void rotateRight();
		
	protected:
		shared_ptr<BinaryNode<Student>> root_ptr_;
		auto copyTree(const std::shared_ptr<BinaryNode<Student>> old_tree_root_ptr) const;
		void destroyTree(shared_ptr<BinaryNode<Student>> sub_tree_ptr);
		int getHeightHelper(shared_ptr<BinaryNode<Student>> sub_tree_ptr) const;
		auto placeNode(shared_ptr<BinaryNode<Student>> subtree_ptr,
				std::shared_ptr<BinaryNode<Student>> new_node_ptr);
		
		bool removes(Student styudent);
		auto removeNode(shared_ptr<BinaryNode<Student>> node_ptr);
		shared_ptr<BinaryNode<Student>> removeLeftmostNode(shared_ptr<BinaryNode<Student>>
				nodePtr, Student& inorderSuccessor);
				
		auto removeValue(shared_ptr<BinaryNode<Student>>
			subtree_ptr, const Student target, bool& success);
		void inorderTraverse(Printer& prints) const;	
		void inorder(Printer& printer,
			shared_ptr<BinaryNode<Student>> tree_ptr) const;

};

#endif