#include "dialog.hpp"

// θ(input.lenght)
void dialog::dialog(easy_dial &easy, const string &input,
                    vector<string> &answers, nat &numtelf) throw()
{
    try {
        unsigned int i = 0;
        answers.push_back(easy.inici());
        while (i < input.size()){ 

            if (input[i] == phone::ENDCHAR){
                answers.push_back(easy.seguent(phone::ENDPREF));
            }

            else if ( input[i] == phone::DELETECHAR ){
                answers.push_back(easy.anterior());
            }

            else {
                answers.push_back(easy.seguent(input[i]));
            }
            ++i;
        }

        numtelf = easy.num_telf();
   }
   catch (error no_troba){
        answers.push_back(no_troba.mensaje());
        numtelf = 0;
   }
}
