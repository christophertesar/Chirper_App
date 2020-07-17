#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
 
#pragma once 
 
#define MSG 180
const char heart[] = "\xe2\x99\xa5";
const char arrow[] = "\xe2\x86\x94";
 
struct post{
 	std::string message; //must not exceed 180 characters
 	bool like;
 	int num_likes;
 	bool reChirp;
 	post *previous;
 	post *next;
};
 
typedef post* postPtr;
class Chirp; //define chirp, as chirp contains an instance of itself
class Chirp{
	private:
	
	 	std::string user;
	 	std::string display_name;
	 	
		postPtr head; //head
		bool isEmpty(postPtr);
		postPtr previous_chirp(postPtr);
		postPtr next_chirp(postPtr);
		void display_chirp(postPtr,std::string,std::string);
		void add_like(postPtr);
		void add_chirp_post();
		void delete_chirp(postPtr&,postPtr&);
		char* scroll_thru_posts();
		bool add_like(int msg);
		void scroll_my_posts(postPtr&,std::string,std::string);
		void scroll_thru_friend_posts(postPtr&);
		void add_friends();
		void reChirp(postPtr&);
		void change_dn();
		
		void pushPost(postPtr&, std::string);
		
		void dispmsg(postPtr);
		
		void deleteList(postPtr&);
		
	public:
		Chirp(); //constructor
		Chirp(const Chirp &o);//copy constructor
		Chirp *friends; //one friend
		~Chirp(); //destructor
		void setup_account();
		void menu();
		void setUser(std::string);
		std::string getUser();
		void setDN(std::string);
		std::string getDN();                                
};
