#include<Windows.h>
#include<tchar.h>
#include<winuser.h>
#include<cstring>
#include<iostream>
using namespace std;

	HHOOK keyboardHook{NULL};
		bool Btn_state=false;
		int ctrlButton=0;
		
			//mouuse handler
		auto x=0;
		auto y=0;
		bool clicking;
		bool user_set=false;
		void startClickHandler();
		void  startKeyboardHook();
		
		//time handling
		auto time_frame=0;
		char choice;
		auto interval=3;
		
		
		void CALLBACK 	startClick(HWND hwnd,UINT uMsg,UINT timerId,DWORD dwTime){
			try{
			if(!clicking && user_set){
			 	clog<<"----------------clicking stopped..."<<endl;    //GetAsyncKeyState(VK_NUMPAD3	
				user_set=false;
		}
					else if(clicking && user_set){
						clog<<"----------------click initiated..."<<endl;
				
					SetCursorPos(x,y);
					mouse_event(MOUSEEVENTF_LEFTDOWN,x,y,0,0);
					mouse_event(MOUSEEVENTF_LEFTUP,x,y,0,0);
				}
				else 	clog<<"Location: ("<<x<<","<<y<<")"<<endl;
}
catch(...){ clog<<"Error detected"<<endl;}
	}
		
		
		
		LRESULT CALLBACK KeyboardProcessor(const int code,const WPARAM wparam,const LPARAM lparam){
			if(code>=0 && (wparam==WM_KEYDOWN || wparam==WM_SYSKEYDOWN)){
					KBDLLHOOKSTRUCT* pressedKey=(KBDLLHOOKSTRUCT*)lparam;
   				char xchar;
				
				if(!Btn_state){ //no btn set!! ToAscii(pressedKey->vkCode,pressedKey->scanCode,0,(LPWORD)&xchar,0);	
				if(pressedKey->vkCode==27 || pressedKey->vkCode==97 || pressedKey->vkCode==99){
				 clog<<"-->This key is reserved,select another"<<endl;
		//		cin>>ctrlButton;
			}
					else{
			//	 clog<<pressedKey->vkCode<<" "<<(char)pressedKey->vkCode<<" has been pressed"<<endl;
				 ctrlButton=pressedKey->vkCode;
				 Btn_state=true;
				 clog<<"key\t"<<ctrlButton<<"\t has been set for control"<<endl;
				 
				 clog<<"Select the timeFrame to use(eg H for hours,m for mins,s for seconds,x for milliseconds\n";
					cin>>choice;
				 
				clog<<"-->Select the click interval in "<<choice<<endl;
			  cin>>interval;
			  
	    	if((int)interval==0){
			  clog<<"!!!invalid input"<<endl;
				Sleep(2000);
				system("exit");
			}
			else{
				switch(choice){
					case 'H': time_frame=interval*3600000;
					break;
						case 'm': time_frame=interval*60000;
					break;
						case 's': time_frame=interval*1000;
					break;
						case 'x': time_frame=interval;
					break;
				}
				
				
						SetTimer(NULL,0,time_frame,(TIMERPROC)& startClick);
			  clog<<"-->Positon your cursor at the required position and Press \'numpad-1\' or \'Enter\' to save location(click twice)"<<endl;
			  clog<<"-->now you can press the above key again to start autoclicking"<<endl;
			}
		}
		}
			else{
					 if(pressedKey->vkCode==ctrlButton){
					 clicking=clicking==false?true:false;  //toggling the click state
					 user_set=true;
			}
		  else	startClickHandler();
		}
	}
	
			return CallNextHookEx(keyboardHook,code,wparam,lparam);
		} 
	
		
   void startKeyboardHook(){	
			
			keyboardHook=SetWindowsHookEx(WH_KEYBOARD_LL,(KeyboardProcessor),NULL,0);
			MSG msg;

			clog<<"**********keyboard sniffing started...*********************"<<endl;
			clog<<"-->Press the key you prefer to control clicking"<<endl;	
		
		while(GetMessage(&msg,NULL,0,0)){
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			
			UnhookWindowsHookEx(keyboardHook);  //very_important
		}
		
		
		
		
		void startClickHandler(){
			
				if(GetAsyncKeyState(VK_NUMPAD1) || GetAsyncKeyState(VK_RETURN)){
				//	Sleep(1000);
					
					POINT cursorPos;
					GetCursorPos(&cursorPos);
					x=cursorPos.x;
					y=cursorPos.y;
					
					clog<<"mouse x:"<<x<<"\nmouse y:"<<y<<endl;
				}
				
				
				if(GetAsyncKeyState(VK_ESCAPE)){ //not well,but fine yet
					clog<<"Obtaining coords"<<endl;
		}
	}
		
		
		
		void initiateHandler(){
			
			clicking=false;
			
			system("TITLE chargedClicker");
			
			clog<<"[HOTKEYS]\n\n";
			clog<<"NUMPAD1:\t saves mouse cursor position\n";
				clog<<"NUMPAD2:\t starts the autoclicker(optional)\n";
			clog<<"NUMPAD3:\tstops the autoclicker\n";
			clog<<"ESC: closes the program\n\n___________________________________________________________\n";
			
			startKeyboardHook();
		}
		
		
		
		
		
		
		
		
		
		
		
		
