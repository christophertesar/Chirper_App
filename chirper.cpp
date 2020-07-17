#include "chirper.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>

Chirp::Chirp(){
	head = NULL; //initialize head to NULL
	//head -> next = NULL;
	//head -> previous = NULL;
	
}

Chirp::~Chirp(){
	Chirp::deleteList(head);
}

void Chirp::menu(){
	std::string state;
	bool exit = false;    //while loop exit condition

	while(exit == false){ //Finite state machine with 5 states
		std::cout << "Please select an option\n\n1.Chirp\n2.Scroll through your Chirps\n3.Scroll through a friends feed\n4.Change your display name\n5.Exit\n\n>>";
		std::getline(std::cin, state);
			
		if(state == "1"){
			Chirp::add_chirp_post();
		}
			
		else if(state == "2"){
			Chirp::scroll_my_posts(head,display_name,user);
		}
				
		else if(state == "3"){
			Chirp::scroll_thru_friend_posts(friends->head);
		}
			
		else if(state == "4"){
			Chirp::change_dn();
		}
					
		else if(state == "5"){
			exit = true;
		}
				
		else{
			std::cout << "Command not recognized.\n" << std::endl;
		}
				
	}

}

void Chirp::scroll_thru_friend_posts(postPtr& head){
	Chirp::scroll_my_posts(head,friends->display_name,friends->user);
}

void Chirp::add_friends(){
	std::ifstream file("friends_list.dat");
	std::string word;

	if(!file){
		std::cout << "Can not find the specified file\n";
		exit(1); //terminate with an error
	} //else opened just fine
	//Chirp f; //make a new member "friends" of the class
	file >> word;

	friends = new Chirp;
	friends->setUser(word);
	file >> word;
	friends->setDN(word);

	//std::cin.ignore();
		for(std::string line; std::getline(file, line); ){
			if(line == "") continue;
				line.resize(MSG); //as a precaution
				friends->pushPost(friends->head,line);
		  }
}

void Chirp::deleteList(postPtr& head){
	
	postPtr current = head;
	postPtr nxt;
	
	while (current != NULL){
		nxt = current->next;
		delete current;
		current = nxt;
	}
	head = NULL;
}

postPtr Chirp::previous_chirp(postPtr temp){
	postPtr previous = temp->previous;       //Inputs temp, declares "previous" pointer which points to previous post, returns previous.
	return previous;
}

postPtr Chirp::next_chirp(postPtr temp){
	postPtr next = temp->next;              //Same as previous_chirp
	return next;
}

void Chirp::display_chirp(postPtr post,std::string display_name,std::string user){
		std::string msg;
		msg = post->message;
		
		std::cout << "_______________________________________________\n";
		std::cout << "|" << std::left << std::setw(20) << display_name << "    " << "@" << std::left << std::setw(20) << user << "|\n";                        
		std::cout << "|" << std::left << std::setw(45) << msg << "|\n";
		std::cout << "       Likes:" << heart << std::left << std::setw(2) << post->num_likes << "       ReChirps:";
		if(post->reChirp == true)
			std::cout << arrow;
		else
			std::cout << " ";
		std::cout << std::left << std::setw(23) << std::endl;
		std::cout << "_______________________________________________\n\n";
}


void Chirp::scroll_my_posts(postPtr& head,std::string display_name,std::string user){
	std::string option;
	bool exit = false;
	postPtr temp = head;
	std::cout << display_name << "'s posts:" << std::endl;
	
	if (temp == NULL){
		std::cout << "There are no more Chirps!" << std::endl; //If "head" is pointing to NULL, there were no posts posted.
	}
	
	else{
		Chirp::display_chirp(temp,display_name,user);                           //If "head" (or in this case temp) is not pointing to NULL, as post has been posted and will display the head contents.
	}
	
	while(exit == false){
		std::cout << "(p)revous,(n)ext,(l)ike,(d)elete,(r)eChirp or e(x)it:\n>>";
		std::getline(std::cin, option);
		
		if(option == "p" || option == "P"){ //Previous Chirp                              
			if(temp == NULL){		                                      //Case when there is no posts
				std::cout << "There are no more Chirps!" << std::endl;
			}
			else if (Chirp::previous_chirp(temp) == NULL){                //Case when we are at the top of the list
				std::cout << "There are no more Chirps!" << std::endl;
			}
			
			else{
				temp = Chirp::previous_chirp(temp);                       //Not at end and list isnt empty; display chirp
				Chirp::display_chirp(temp,display_name,user);
			}
		}
		
		else if(option == "n" || option == "N"){ //Next Chirp
			if(temp == NULL){                                             //Case when there is no posts
				std::cout << "There are no more Chirps!" << std::endl;
			}
			else if (Chirp::next_chirp(temp) == NULL){					  //Case when we are at the end of the list
				std::cout << "There are no more Chirps!" << std::endl;
			}
			
			else{                                                         //Display chirp.
				temp = Chirp::next_chirp(temp);
				Chirp::display_chirp(temp,display_name,user);
			}
		}
		
		else if(option == "l" || option == "L"){ //Like Chirp
			if(temp == NULL){
				std::cout << "There is no tweet to like!" << std::endl;
			}
			else if(temp->like == true){
				std::cout << "This tweet is already liked!" << std::endl;
			}
			else
			{
				Chirp::add_like(temp);
				Chirp::display_chirp(temp,display_name,user);
			}
		}
		
		else if(option == "r" || option == "R"){
			if(temp == NULL){
				std::cout << "There is no Chirp to reChirp!" << std::endl;
			}
			else if(temp->reChirp == true){
				std::cout << "This Chirp has already been reChirped!" << std::endl;
			}
			else{
				Chirp::reChirp(temp);
				std::cout << "reChirped!" << std::endl;
				Chirp::display_chirp(temp,display_name,user);
			}
		}
		
		else if(option == "d" || option == "D"){
			if(temp == NULL){
				std::cout << "There is no Chirp to delete!\n" << std::endl;
			}
			else{
				Chirp::delete_chirp(temp,head);
				std::cout << "Chirp deleted!\n" << std::endl; 
				}
		}
		
		else if(option == "x" || option == "X"){
			exit = true;
		}
		
		else{
			std::cout << "Command not recognized." << std::endl;
		}
		
		
	}
}

void Chirp::reChirp(postPtr& temp){
	temp->reChirp = true;
	Chirp::pushPost(head, temp->message);
}

void Chirp::delete_chirp(postPtr& temp,postPtr& head){ //Precondition: postPtr must not be pointing to NULL
	if(temp == NULL){
		std::cout << "There is no tweet to delete!" << std::endl;
	}
	else{
		postPtr current = temp;
		if(temp->next == NULL && temp->previous == NULL){
			delete current;
			temp = NULL;
			head = NULL;
		}
		else if(temp->next == NULL){
			postPtr prev = current->previous;
			prev->next = current->next;
			temp = current-> previous;
			delete current;
		}
		else if(temp->previous == NULL){
			postPtr nxt = current->next;
			nxt->previous = NULL;
			head = current->next;
			temp = current->next;
			delete current;
		}
		else{
			postPtr prev = current->previous;
			postPtr nxt = current->next;
			
			prev->next = current->next;
			nxt->previous = current->previous;
			temp = current->previous;
			delete current;
		}
	}
}

void Chirp::add_like(postPtr temp){
	temp->like = true;
	temp->num_likes = temp->num_likes + 1;
	std::cout << "Liked post!\n" << std::endl;
}

void Chirp::dispmsg(postPtr head){
	postPtr temp = head;
	while(temp->next != NULL){
		std::cout << temp->message << std::endl;
		temp=temp->next;
	}
}

void Chirp::pushPost(postPtr& head, std::string msg){   
	if(head == NULL){
		postPtr temp_ptr;
		temp_ptr = new post;
		temp_ptr -> previous = NULL;  //initializing post properties
		temp_ptr -> next = NULL;
		temp_ptr -> message = msg;
		temp_ptr -> num_likes = 0;
		temp_ptr -> like = false;
		temp_ptr -> reChirp = false;
		head = temp_ptr;
	}
	else {
		postPtr temp_ptr;
		temp_ptr = new post;    
		temp_ptr->previous = NULL; //initializing post properties
		temp_ptr->message = msg;
		temp_ptr->num_likes = 0;
		temp_ptr-> like = false;
		temp_ptr-> reChirp = false;
		
		temp_ptr->next = head;     
		head->previous = temp_ptr;
		head = temp_ptr;
	}                          
}

bool isEmpty(postPtr head){
	if (head->previous == NULL){
	return true;
	}
	else{
	return false;
	}
}

void Chirp::add_chirp_post(){
	std::string post;
	bool valid_post = false;
	
	std::cout << "What would you like to post?\n>> ";
	//std::cin.ignore();
	std::getline(std::cin, post);
	
	if (post.size() > MSG){
		std::cout << "Character limit is 180 max." << std::endl;
	}
	else{
		Chirp::pushPost(head, post);
	}
}



void Chirp::change_dn(){
	std::string newName;
	std::cout << "Please enter your new display name: \n>>";
	//std::cin.ignore();
	std::getline(std::cin, newName);
	Chirp::setDN(newName);
	std::cout << "OK your new display name is: " << newName << std::endl << std::endl;
}

void Chirp::setup_account(){
	std::string tempDispName;
	std::string tempUsername;
	
	std::cout << "Lets get your Twitter... I mean Chirper account setup!" << std::endl;
	std::cout << "Username:\n>>";
	//std::cin.ignore();
	std::getline(std::cin, tempUsername);
	Chirp::setUser(tempUsername);
	
	std::cout << "Display Name:\n>>";
	//std::cin.ignore();
	std::getline(std::cin, tempDispName);
	Chirp::setDN(tempDispName);
	
	Chirp::add_friends();
	std::cout << "\n>> Adding friends..." << std::endl;
	std::cout << "\n>> OK you are ready to go!" << std::endl;
}


std::string Chirp::getUser(){
	return user;
}

void Chirp::setUser(std::string username){
	user = username;
}

void Chirp::setDN(std::string dn){
	display_name = dn;
}
