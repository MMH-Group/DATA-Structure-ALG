#include<iostream>
using namespace std;

class Song{
	public:
		string name;
		string title;
		Song* prev;
		Song* next;
		
		Song(){
			name="";
			title="";
			prev=NULL;
			next=NULL;
		}	
};
class playlist{
	Song* head;
	Song* current;
	int count=0;
	public:
		playlist(){
			head=NULL;
			current=NULL;
		}
		void addsong(){
			Song* newsong=new Song();
			
			cout<<"Enter Song Name:";
			cin>>newsong->name;
			cout<<"Enter Song Title:";
			cin>>newsong->title;
			if(head==NULL){
				head=newsong;
				newsong->next=NULL;
				newsong->prev=NULL;
				current=newsong;
				count++;
				return;
			}else{
				Song* temp=head;
				while(temp->next){
					temp=temp->next;
				}
				newsong->prev=temp;
				temp->next=newsong;
			}
			current=newsong;
			count++;
		}
		
		void playcurrentsong(){
			if(count<1){
				cout<<"\n No Song is currently in the list.\n";
				return;
			}
			cout<<"\nPlaying Song...........\n";
			cout<<"Name: "<<current->name<<endl;
			cout<<"Title: "<<current->title<<endl;
			
		}
		void nextsong(){
			if(current->next==NULL){
				cout<<"\nThere is no Next Song\n";
				return;
			}
			cout<<"\nMoving to the next Song.\n";
			current=current->next;
			
		}
		void prevsong(){
			if(current->prev==NULL){
				cout<<"\nThere is no Previous Song\n";
				return;
			}
			cout<<"\nMoving to the previous Song.\n";
			current=current->prev;
		}
};
int main(){
	playlist youtube;
	int n;
	menu:
	cout<<"\n----Menu----\n";
	cout<<"\n1. Add a Song";
	cout<<"\n2. Play Current Song";
	cout<<"\n3. Previous Song";
	cout<<"\n4. Next Song";
	cout<<"\n5. Exit App";
	
	cout<<"\nEnter your choice:";
	cin>>n;
	
	switch(n){
		case 1:{
			youtube.addsong();
			goto menu;
		}
		case 2:{
			youtube.playcurrentsong();
			goto menu;
		}
		case 3:{
			youtube.prevsong();
			goto menu;
		}
		case 4:{
			youtube.nextsong();
			goto menu;
		}
		case 5:{
			cout<<"\nThe Application is Closing..............\n";
			break;
		}
		default:{
			cout<<"\n Invalid Enter! Chose form the menu.\n";
			goto menu; 
		}
	}
}
