//Sam Louvall
///Lexical analyzer


#include <iostream>
#include <string>
using namespace std;

int recognizeType(string s); 



int main()
{
  int numEntries;
  string s;

  cin >> numEntries;
  cout << endl << endl << numEntries <<endl; 
  for(int i = 0; i < numEntries;i++)
  {
    cin >> s; 
    cout << i+1 <<":  ";

    //feeding recognize type function a string to figure out the type. 
    switch (recognizeType(s))
    {
      case 2:
        cout<<"Integer";
        break;
      case 4:
        cout<<"Decimal";
        break;
      case 5:
        cout<<"Scientific";
        break;
      case 7:
        cout<<"Hexadecimal";
        break; 
      case 8:
        cout<<"Character";
        break;
      case 10:
        cout<<"Identifier";
        break;
      case 15:
        cout<<"Keyword";
        break;
      case 20:
        cout<<"String";
        break; 
      default:
        cout<<"INVALID!";
        break;  



    } //End switch 
    
  cout << endl; 

  }//end for 
  return 0;  
}

int recognizeType(string s)
{
  int state = 1;
  int i = 0; 
  int length = s.length();
  bool sign = false; 

  while( i < length)
  {
    switch(state)
    {
      //START STATE
      case 1: 
        if(s[i] == '+' || s[i] == '-')
        { //to intermediate int or scientific  or decimal 
          state = 2;
          sign = true;
        }

        else if(s[i] >= '0' && s[i] <= '9') //Integer, Decimal or hex
        {                                     
          state = 2; 
        }
        else if(s[i] == 'W')//(w)hile 
        {
          //CHECK KEYWORD OR SEND TO HEX STATE
          state = 11; 
          break; 
        }
        else if(s[i] == 'I')
        {
          
          state = 16;
        }
        else if(s[i] == 'E')//(E)LSE
        {
          //CHECK KEYWORD HEX OR ID
          state = 17;

        }
        else if(s[i] >= 'A'|| s[i] == 'B' || s[i] == 'C' || s[i] == 'D' || s[i] == 'F' || s[i] == 'E')
        {  
          state = 9;//semi id
        }
        else if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'G' && s[i] <= 'Z')) ///IDENTIFIER 
        {
  
          state = 10; 
          
        }  
        else if(s[i] == '"')// SEND TO STRING LITERAL 
        {
          //STRING LITERAL 
          state = 20;
        }
        else  
          state = -1;
        break;


      //INT ACCEPT OR SCIENTIFIC OR DECIMAL OR HEX 
      case 2:
        if(s[i] >= '0' && s[i] <= '9') //To: INTEGER
        {
          state = 2;  
        }
        else if(s[i] == '.') //could be decimal, scientific 
        {
          state = 3;
           
        }
        else if(s[i] >= 'A' && s[i] <= 'F') // SEND TO HEX OR ID OR Character literal 
        { 
          state = 6; 
        }
        else  
          state = -1;
        break; 



      
        //sent here cause could be decimal, scientific or hex 
       case 3:
        if(s[i] >= '0' && s[i] <= '9') //decimal or scientific or hex 
          {
            state = 4;
          }
          else if(s[i] >= 'A' && s[i] <= 'F')
          {
            state = 6; //send to hex 
          }
          else  
            state = -1;
        break; 
        



        case 4:
          if(s[i] >= '0' && s[i] <= '9') //decimal [ACCEPT]
          {
            state = 4;
  
          }
          else if(s[i] == 'E') //possibly scientiic 
          {
            state = 5; 
          }
          else 
            state = -1;
          break;
        
        //scientific 
        case 5:
          if((s[i] >= '0' && s[i] <= '9') || s[i] == '-')
          {
            state = 5; 
          }
          else  
            state = -1;
          break; 




        //CHECKING IF HEX
        case 6:
          if ((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'A' && s[i] <= 'F'))
            state = 6;
          else if (s[i] == 'H')//to hex only 
          {
            state = 7;
          }
          else if(s[i] == 'X')
          {
            state = 8;
          }              
          else
            state = -1;
          break;


        //LAST THING ON HEX BECAUSE ANYTING ELSE WOULD BE INVALID 
        case 7:
          state = -1;
        break; 

        //LAST THING ON CHARACTER LITERAL BC ANYTHING AFTER WOULD BE INVALID 
        case 8:
          state = -1;
        break; 

        //IDENTIFIER or HEX OR CHARACTER LITERAL
        case 9:
          if((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'A' && s[i] <= 'F'))
          {
            state = 6;
          }
          else if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'G' && s[i] <= 'Z'))
          {
            state = 10; 
          }
          else if(s[i] >= '0' && s[i] <= '9')
          {
            //id state
            state = 10;
          }
          else if(s[i] == '_')
          {
            state = 10; 
          }
          else
            state = -1;
          break; 
        

        ///ID ACCEPT 
        case 10:
          if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
          {
            
            state = 10; 
          }
          else if(s[i] >= '0' && s[i] <= '9')
          {
              state = 10; 
          }
          else if(s[i] == '_')
          {
            state = 10;
          }
          else  
            state = -1;
        break; 


        case 11: //W(H)ILE
          if(s[i] == 'H')
          {
            state = 12; 
            break; 
          }
          else if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] == '_') || (s[i] >= '0' && s[i] <= '9'))
          {
            state = 9; 
          }
          else  
            state = -1;
        break; 

        case 12: //WH(I)LE
          if(s[i] == 'I')
          {
            
            state = 13; 
            break; 
          }
          else if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] == '_') || (s[i] >= '0' && s[i] <= '9'))
          {
            state = 9; 
          }
          else  
            state = -1;
        break; 

        case 13: //WHI(L)E
          if(s[i] == 'L')
          {
          
            state = 14; 
            break; 
          }
          else if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] == '_') || (s[i] >= '0' && s[i] <= '9'))
          {
            state = 9; 
          }
          else  
            state = -1;
        break; 

        case 14: //WHIL(E)
          if(s[i] == 'E')
          {
           
            state = 15; 
            break; 
          }
          else if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] == '_') || (s[i] >= '0' && s[i] <= '9'))
          {
            state = 9; 
          }
          else  
            state = -1;
        break; 

        //KEYWORD ACCEPT SECURITY BLANKET 
        case 15:
        if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] == '_') || (s[i] >= '0' && s[i] <= '9'))
        {
          state = 10;
        }
        else  
          state = -1;
        break;

      //IF
      case 16:
      if(s[i] == 'F')
      {
        state = 15; 
      }
      else if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] == '_') || (s[i] >= '0' && s[i] <= '9'))
      {
        state = 10; 
      }
      else
        state = -1;
      break;

      ///ELSE
      case 17:
        if(s[i] = 'L')
        {
          state = 18;
        }
        else if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] == '_') || (s[i] >= '0' && s[i] <= '9'))
        {
          state = 6; 
        }
        else  
          state = -1;
      break;

      //EL(S)E
      case 18:
        if(s[i] = 'S')
        {
          state = 19;
        }
        else if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] == '_') || (s[i] >= '0' && s[i] <= '9'))
        {
          state = 10; 
        }
        else  
          state = -1;
      break; 

      case 19:
        if(s[i] = 'E')
        {
          state = 15; //SEND TO KEYWORD ACCEPT 
        }
        else if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] == '_') || (s[i] >= '0' && s[i] <= '9'))
        {
          state = 10; 
        }
        else  
          state = -1;
      break;  

      //string literal
      case 20:
      if(s[length -1] == '"')
      {
        state = 20;
      }
      else
        state = -1;
      break; 

      




      





       


      


      //fail state   
      default:
        i = length; 
        break;

        
        
        


    }// end switch 
    i++; 


  }//end while


  return state; 

}