#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <map>
using namespace std;

enum condition
{
    START, PER, FIN, COM, ERR, INC_OPEN, TKN, INC_CLOSE, GRAM, CODE, GRAM_END, NOT_GRAM, GRAM_WORD
};

enum lex
{
  l_NULL, /*0*/
  l_INC_BEG, l_INC_END, l_INC, l_TOKEN, l_GR_BEG, l_GR_END, l_SEMICOLON, l_COLON, l_OR, l_OPEN,/*10*/
  l_CLOSE, l_COM, l_STRING_I, l_STRING_CODE, l_STRING_LR, l_STRING_RR, l_ERR, l_FIN, l_TOKEN_OPEN /*17*/
  }; /*41*/
 

 
class Lexema
{
    lex t_lex;
    string v_lex;
public:
    Lexema (lex t = l_NULL, string v = "")  {
        t_lex =t; v_lex=v;
    }
    lex  get_type ()  { return t_lex; }
    string get_value () { return v_lex; }
bool operator == (lex l)
    {
        if (t_lex == l)
            return true;
        else return false;
    }
    bool operator != (lex l)
    {
        return !(t_lex == l);
    }
};

class Lexeme_analyse
{
    int column,  row;
    vector<Lexema> lexems;
    FILE* file;
    char c;
    condition current;
    bool stool;
public:
    Lexeme_analyse(FILE* f):file(f), current(START), column(1), row(0)
    {}
    vector<Lexema> parse()
    {
        return lexems;
    }
    bool get_lexems()
    {
        Lexema current_lex;
        while(current_lex.get_type() != l_FIN && current_lex.get_type() != l_ERR)
        {
            //cout << current_lex.get_type() << endl;
            current_lex = get_lex();
            lexems.push_back(current_lex);
        }
        if (current_lex.get_type() == l_ERR)
        {
            cout << "Строка :" << column << " Столбец: " << row << " Символ: " << c << endl;
            return false;
        }
        if (current_lex.get_type() == l_FIN)
            return true;
    }
    Lexema get_lex()
    {
        condition prev_condition;
        while(current != FIN)
        {
            int flag = 0;
            string tmp = "";
            switch(current)
            {
                case START:
                    c = fgetc(file);
                    while (c == ' ' || c == '\n')
                    {
                        if (c == ' ') row++;
                        else {
                            row = 0;
                            column++;
                        } 
                        c = fgetc(file);
                    }
                    if (c != '\n' && c != EOF) row++;
                        else if (c == '\n'){
                            row = 0;
                            column++;
                        } 
                    if (c == EOF) 
                        return Lexema(l_FIN);
                    if(c == '%')
                        current = PER;
                    else if (c == '/')
                    {
                        prev_condition = current;
                        current = COM;
                    }
                    else
                        current = ERR; 
                    break;
                case PER:
                    c = fgetc(file);
                    if (c != '\n' && c != EOF) row++;
                        else if (c == '\n'){
                            row = 0;
                            column++;
                        } 
                    if (c == '{')
                    {
                        current = INC_OPEN;
                        return Lexema(l_INC_BEG);
                    }
                    else if(c == '%')
                    {
                        current = GRAM;
                        return Lexema(l_GR_BEG);
                    }
                    else if(c == 't')
                    {
                        current = TKN;
                        return Lexema(l_TOKEN_OPEN);
                    }
                    else 
                        current = ERR;
                    break;
                case INC_OPEN:
                    c = fgetc(file);

                    while (c != '%' && c != EOF)
                    {
                        if (c != '\n' && c != EOF) row++;
                        else if (c == '\n'){
                            row = 0;
                            column++;
                        } 
                        tmp += c;
                        c = fgetc(file);
                    }
                    if (c != '\n' && c != EOF) row++;
                        else if (c == '\n'){
                            row = 0;
                            column++;
                        } 
                    if (c == EOF)
                        current = ERR;
                    else 
                    {
                        current = INC_CLOSE;
                        return Lexema(l_INC, tmp);
                    }
                    break;
                case CODE:
                    c = fgetc(file);
                    while (c != '}' && c != EOF)
                    {
                        if (c != '\n' && c != EOF) row++;
                        else if (c == '\n'){
                            row = 0;
                            column++;
                        } 
                        tmp += c;
                        c = fgetc(file);
                    }
                    if (c != '\n' && c != EOF) row++;
                        else if (c == '\n'){
                            row = 0;
                            column++;
                        } 
                    if (c == EOF)
                        current = ERR;
                    else 
                    {
                        current = GRAM;
                        return Lexema(l_STRING_CODE, tmp);
                    }
                    break;    
                case INC_CLOSE:
                    c = fgetc(file);
                    if (c != '\n' && c != EOF) row++;
                        else if (c == '\n'){
                            row = 0;
                            column++;
                        } 
                    if(c == '}')
                    {
                        current = START;
                        return Lexema(l_INC_END);
                    }
                    else
                        current = ERR;
                    break;
                case TKN:
                    for (int i = 0; i < 5; i++)
                    {
                        c = fgetc(file);
                        tmp += c;
                        if (c != '\n' &&c != EOF) row++;
                        else if (c == '\n'){
                            row = 0;
                            column++;
                        } 
                    }    
                    if (tmp == "oken ")
                    {
                        tmp = "";
                        c = fgetc(file);
                        while (c != ';' && c != EOF)
                        {
                            if (c != '\n' && c != EOF) row++;
                        else if (c == '\n'){
                            row = 0;
                            column++;
                        } 
                            tmp += c;
                            c = fgetc(file);
                        }
                        if (c != '\n' && c != EOF) row++;
                        else if (c == '\n'){
                            row = 0;
                            column++;
                        } 
                        if (c == ';')
                        {
                            current = START;
                            return Lexema(l_TOKEN, tmp);
                        }    
                        else
                            current = ERR;
                    }
                    break;
                case COM:
                    c = fgetc(file);
                    if (c != '\n' && c != EOF) row++;
                        else if (c == '\n'){
                            row = 0;
                            column++;
                        } 
                    if (c == '*')
                    {
                        c = fgetc(file);
                        if (c != '\n' && c != EOF) row++;
                        else if (c == '\n'){
                            row = 0;
                            column++;
                        } 
                        while (c != '*' && c != EOF)
                        {
                            tmp += c;
                            c = fgetc(file);
                            if (c != '\n' && c != EOF) row++;
                        else if (c == '\n'){
                            row = 0;
                            column++;
                        } 
                            if (c == '*')
                            {
                                c = fgetc(file);
                                if (c != '\n' && c != EOF) row++;
                        else if (c == '\n'){
                            row = 0;
                            column++;
                        } 
                                if (c == '/')
                                {
                                    current = prev_condition;
                                    return Lexema(l_COM, tmp);
                                }
                            }     
                        }
                    }    
                    current = ERR;  

                    break;
                case GRAM:
                    c = fgetc(file);
                    if (c != '\n' && c != EOF) row++;
                        else if (c == '\n'){
                            row = 0;
                            column++;
                        } 
                    while (c == ' ' || c == '\n')
                    {
                        c = fgetc(file);
                        if (c != '\n' && c != EOF) row++;
                        else if (c == '\n'){
                            row = 0;
                            column++;
                        } 
                    }
                    if (c == EOF) return Lexema(l_ERR);
                    if (c == '/')
                    {
                        prev_condition = current;
                        current = COM;
                    }    
                    else if(c == '|')

                        return Lexema(l_OR);
                    else if(c == ';')
                        return Lexema(l_SEMICOLON);
                    else if(c == '{')
                        current = CODE;
                    else if(c == '%')
                    {
                        c = fgetc(file);
                        if (c != '\n' && c != EOF) row++;
                        else if (c == '\n'){
                            row = 0;
                            column++;
                        } 
                        if (c == '%')
                        {
                            current = GRAM_END;
                            return Lexema(l_GR_END);
                        }
                        else
                            current = ERR;
                    }
                    else
                    {   
                        while (c != ':' && c != ' ' && c != '\n' && c != EOF && c != '|')
                        {
                            tmp += c;
                            c = fgetc(file);
                            if (c != '\n' && c != EOF) row++;
                        else if (c == '\n'){
                            row = 0;
                            column++;
                        } 
                        }
                        if (c == ':')
                        {
                            return Lexema(l_STRING_LR, tmp);
                        }
                        else if (c == ' ' || c == '\n' || c == '|')
                        {
                            flag = 1;
                            return Lexema(l_STRING_RR, tmp);
                        }
                        else 
                            current = ERR;
                    }
                    break;
                case GRAM_END:
                    current = NOT_GRAM;
                    break;   
                case ERR:
                    return Lexema(l_ERR); 
                case NOT_GRAM:
                    c = fgetc(file);
                    if (c != '\n' && c != EOF) row++;
                        else if (c == '\n'){
                            row = 0;
                            column++;
                        } 
                    while(c != EOF)
                    {
                        tmp += c;
                        c = fgetc(file);
                        if (c != '\n' && c != EOF) row++;
                        else if (c == '\n'){
                            row = 0;
                            column++;
                        } 
                    }
                    current = START;
                    return Lexema(l_COM, tmp);                          
            }
                    
        }
    }
};

class Syntax
{

    vector<Lexema> lexems;
    bool error;
    int i;
public:
    Syntax(vector<Lexema> l) :lexems(l), error(false), i(0){}
    bool analize()
    {
        A();
        B();
        C();
        D();
        if (lexems[i] != l_FIN)
            error = true;
        return !error;
    }
    void A()
    {
        if(error) return;
        if(lexems[i] == l_INC_BEG)
        {
            i++;
            P();
            if(lexems[i] == l_INC_END)
                i++;
        }
    }
    void P()
    {
        if(error) return;
        if(lexems[i] == l_INC)
            i++;
    }
    void B()
    {
        if(error) return;
        U();
        if (lexems[i] == l_TOKEN_OPEN)
            B();
    }
    void D()
    {
        if(error) return;
        if(lexems[i] == l_COM)
            i++;
    }
    void U()
    {
        if(error) return;
        if (lexems[i] == l_TOKEN_OPEN)
        {
            i++;
            if (lexems[i] == l_TOKEN)
                i++;
            else error = true;
        }
        else error = true;    
    }
    void C()
    {
        if(error) return;
        if(lexems[i] == l_GR_BEG)
        {    
            i++;

            T();
            if(!error)
            {
                if (lexems[i] != l_GR_END)
                    error = true;
                else
                    i++;
            }         
        }                
    }
    void T()
    {
        if(error) return;
        E();
        if (lexems[i] == l_STRING_LR)
            T();
    }
    void E()
    {       
        if(error) return;
        Y();
        Z();
        if (lexems[i] == l_SEMICOLON)
            i++;
        else error = true;
    }

    void Y()
    {
        if(error) return;
        if (lexems[i] == l_STRING_LR)
            i++;
        else 
            error = true;
    }
    void Z()
    {
        if(error) return;
        L();
        Q();
        if(lexems[i] == l_OR)
        {
            i++;
            Z();
        }
    }
    void L()
    {
        if(error) return;
        if (lexems[i] == l_STRING_RR)
        {
            i++;
            if (lexems[i] == l_STRING_RR)
                L(); 
        }
        else error = true;
    }
    void Q()
    {
        if(error) return;
        if (lexems[i] == l_STRING_CODE)
            i++;       
    }
};


bool has_string(vector<string>& v, string s)
{
    for (int i = 0; i < v.size(); i++)
        if (v[i] == s) return true;
    return false;
}

class Rule
{
    string left;
    vector<vector<string>> right;
    vector<string> code;   
    int i;
public:
    Rule(string s):left(s),i(0){right.resize(1);}
    void add_right(Lexema l)
    {
        if (l == l_OR)
        {
            if (i == 0)
                right[i].push_back("");
            i++;
            right.resize(i+1);
        }
        else
        {
            right[i].push_back(l.get_value());
        }
    }
    void add_code(string s)
    {
        code.push_back(s);
    }
    string get_left()
    {
        return left;
    }
    vector<vector<string>> get_right()
    {
        return right;
    }
    //friend bool recursive(Parser pars);
};


class Parser
{
vector<Rule> gram;
vector<string> terminals;
vector<Lexema> lexems;    
map<string, vector<string>> first;
map<string, vector<string>> follow;
public:
    Parser(vector<Lexema> l):lexems(l){}
    bool is_terminal(string s)
    {
        for (int k = 0; k < terminals.size(); k++)
            if(s == terminals[k]) 
                return true;
        return false;    
    }
    bool has_noterminal(int& p)
    {
        for(int k = 0; k < gram.size(); k++)
        {
            vector<string> &tmp = first[gram[k].get_left()];
            for(int j = 0; j < tmp.size(); j++)
            {
                if(!is_terminal(tmp[j]))
                {
                    p = k;
                    return true;
                }
            }
        }
        return false;  
    }
    void find_follow()
    {
        bool changed = true;
        for(int k = 0; k < gram.size(); k++)
        {
            follow.insert(std::make_pair(gram[k].get_left(), vector<string>()));
        }
        while(changed)
        {    
            changed = false;
            for(int k = 0; k < gram.size(); k++)
            {
                for(int l = 0; l < gram[k].get_right().size(); l++)
                {
                    for (int p = 0; p < gram[k].get_right()[l].size(); p++)
                    {
                        
                        if(!is_terminal(gram[k].get_right()[l][p]) && p < gram[k].get_right()[l].size() - 1)
                        {
                            auto &tmp = follow[gram[k].get_right()[l][p]];
                            if (!has_string(tmp, gram[k].get_right()[l][p+1]))
                            {
                                changed = true;
                                tmp.push_back(gram[k].get_right()[l][p+1]);
                            }
                            else if(!is_terminal(gram[k].get_right()[l][p+1]))
                            {

                                for(int w = 0; w < tmp.size(); w++)
                                {
                                    if(gram[k].get_right()[l][p+1] == tmp[w])
                                    {
                                        tmp.erase(tmp.begin()+w);
                                        auto& ttt = first[gram[k].get_right()[l][p+1]];
                                        for(int d = 0; d < ttt.size(); d++)
                                            tmp.push_back(ttt[d]);
                                    }

                                }
                            }
                        } 
                    }    
                }
            }
        }
            
    }
    void find_first()
    {
        bool changed = true;
        for(int k = 0; k < gram.size(); k++)
        {
            first.insert(std::make_pair(gram[k].get_left(), vector<string>()));
        }   
        
        for(int k = 0; k < gram.size(); k++)
        {
            for(int j = 0; j < gram[k].get_right().size(); j++)
            {        
                vector<string> &tmp = first[gram[k].get_left()];
                for(int p = 0; p < tmp.size(); p++)
                    if (has_string(tmp, gram[k].get_right()[j][0]))
                        throw string("two identical first");    
                tmp.push_back(gram[k].get_right()[j][0]);
            }
        }   

        while(changed)
        { 
            int t;
            changed = false;  
            if(has_noterminal(t))
            {
                changed = true;
                vector<string>& tmp = first[gram[t].get_left()];
                for(int z = 0; z < tmp.size(); z++)
                {
                    if(!is_terminal(tmp[z]))
                    {
                        string s = tmp[z];
                        tmp.erase(tmp.begin()+z);
                        for (int y = 0; y < first[s].size(); y++)
                        {
                            if (first[s][y] == s)
                            {

                                throw string("error");
                            }
                            else
                            {
                                if(!has_string(tmp, first[s][y]))
                                    tmp.push_back(first[s][y]);
                                else
                                    throw string("two equal first");
                            }
                        }
                    }
                }
            }
        }
    }
    void find()
    {
        int i = 0;
        while(lexems[i] != l_TOKEN_OPEN)
        {
            i++;
        }
        while(lexems[i] == l_TOKEN_OPEN || lexems[i] == l_TOKEN)
        {
            if (lexems[i] == l_TOKEN_OPEN)
                i++;
            else
            {
                terminals.push_back(lexems[i].get_value());
                i++;
            }
        }
        
        while(lexems[i] != l_GR_BEG)
        {
            i++;
        }
        i++;
        while(lexems[i] != l_GR_END)
        {
            
            Rule r(lexems[i].get_value());                
            while(lexems[i] != l_SEMICOLON )
            {
                i++;
                while(lexems[i] != l_STRING_CODE && lexems[i] != l_OR && lexems[i] != l_SEMICOLON)
                {
                    if(lexems[i].get_value()[0]=='\'')
                    {
                        terminals.push_back(lexems[i].get_value());
                    }

                    r.add_right(lexems[i]);
                    i++;
                }
                if(lexems[i] == l_STRING_CODE )
                {
                    r.add_code(lexems[i].get_value());
                    i++;
                }
                else
                    r.add_code("");                
                if(lexems[i] == l_OR)
                    r.add_right(lexems[i]);
            }
            gram.push_back(r);
            i++;
        }
    }
    bool has_this(string s, int p)
    {
        for(int k = 0; k < gram[p].get_right().size(); k++)
            for(int j = 0; j < gram[p].get_right()[k].size(); j++)
                if (gram[p].get_right()[k][j] == s)
                    return true;
        return false;        
    }
    void print()
    {
        cout << "Приведенная грамматика" << endl;
            
        for (int p = 0; p < gram.size(); p++)
        {    
            cout << gram[p].get_left() << ": ";
            for (int k = 0; k < gram[p].get_right().size(); k++)
            {
                for(int t = 0; t < gram[p].get_right()[k].size(); t++)
                {
                    cout << gram[p].get_right()[k][t] << " "; 
                }
                if (k != gram[p].get_right().size()-1) cout << "| ";
            }
            cout << ";"<<endl;    
         }   
    }
    friend void delete_unused(Parser& pars);
    friend void delete_unreach(Parser& pars);
};


void delete_unused(Parser& pars)
{
    vector<string> tmp;
    tmp.push_back(pars.gram[0].get_left());
    bool changed = true;
    while(changed)
    {
        changed = false;
        for(int j = 0; j < pars.gram.size(); j++)
        {
            if(has_string(tmp, pars.gram[j].get_left()))
            {
                for(int k = 0; k < pars.gram[j].get_right().size(); k++)
                {
                    for(int p = 0; p < pars.gram[j].get_right()[k].size(); p++)
                        if(!has_string(tmp, pars.gram[j].get_right()[k][p]))
                        {
                            changed = true;
                            tmp.push_back(pars.gram[j].get_right()[k][p]);
                        }
                }
            }
        }
    }
    for(int p = 0; p < pars.gram.size(); p++)
    {
        if (has_string(tmp, pars.gram[p].get_left()))
        {
            
        }
        else
        {
            pars.gram.erase(pars.gram.begin()+p);

        }
    }
    for(int p = 0; p < pars.terminals.size(); p++)
    {
        if(!has_string(tmp, pars.terminals[p]))
        {
            pars.terminals.erase(pars.terminals.begin()+p);
        }
    }
}

bool equal(vector<string> v1, vector<string> v2)
{
    if(v1.size() != v2.size()) return false; 
    for (int i = 0; i < v1.size(); i++)
    {
        if(v1[i] != v2[i]) return false;
    }
    return true;

}

void delete_unreach(Parser& pars)
{
    vector<string> tmp;
    bool changed = true;
    for(int p = 0; p < pars.gram.size(); p++)
    {
        for(int k = 0; k < pars.gram[p].get_right().size(); k++)
            for(int t = 0; t < pars.gram[p].get_right()[k].size(); t++)
                if(pars.is_terminal(pars.gram[p].get_right()[k][t]) && !has_string(tmp, pars.gram[p].get_right()[k][t]))
                    tmp.push_back(pars.gram[p].get_right()[k][t]);                
    }
    while(changed)
    {
        changed = false;
        for(int p = 0; p < pars.gram.size(); p++)
        {
            for(int k = 0; k < pars.gram[p].get_right().size(); k++)
            {
                bool b = true;
                for(int t = 0; t < pars.gram[p].get_right()[k].size(); t++)
                {
                    if (has_string(tmp, pars.gram[p].get_right()[k][t])){}
                    else b = false;
                }
                if (b && !has_string(tmp, pars.gram[p].get_left()))
                {
                    tmp.push_back(pars.gram[p].get_left());    
                    changed = true;
                }
            }    
        }
    }
    for(int t = 0; t < pars.gram.size(); t++)
    {
        
        if(!has_string(tmp, pars.gram[t].get_left()))
        {
            pars.gram.erase(pars.gram.begin()+t);
        }
        else
        {   
            for(int k = 0; k < pars.gram[t].get_right().size(); k++)
            {

                bool b = true;
                int h = 0;
                        
                for(h = 0; h < pars.gram[t].get_right()[k].size(); h++)
                {
                    if(h != 0 && pars.gram[t].get_right()[k][h] != "")
                        if(!has_string(tmp, pars.gram[t].get_right()[k][h]))
                        {   
                            b = false;    
                        }
                }
                if (!b)
                {
                    pars.gram[t].get_right().erase(pars.gram[t].get_right().begin() + k);    
                    break;
                }   
            }
        }        
    }

    for(int t = 0; t < pars.terminals.size(); t++)
        if(!has_string(tmp, pars.terminals[t]))
            pars.terminals.erase(pars.terminals.begin()+t);               
}

int main (int argc, char* argv[])
{
    try
    {
        FILE* file = fopen("file", "r"); // Здесь имя файла, из которого считываем
        Lexeme_analyse scan(file);
        if(scan.get_lexems())
        {   
            Syntax synt(scan.parse());
            if(synt.analize())
            {
                Parser p(scan.parse());
                p.find();
                delete_unused(p);
                delete_unreach(p);
                p.find_first();
                p.find_follow();
                p.print();
                cout << "Применим метод рекурсивного спуска" << endl;

            }
           
        }
        else
            cout << "Лексическая ошибка" << endl;
    }

    catch(string &s)
    {

        cout << "Метод не применим" << endl;
    }    
    return 0; 
}