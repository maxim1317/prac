#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <sys/ioctl.h>
#define VER 0.1

extern int opterr;
int opterr = 0;

class Errors
{
	char* error_message;
public:
	Errors(const char* c = "")
	{
		int i = 0;
		error_message = new char [256];
		while(c[i])
		{
			error_message[i] = c[i];
			i++;
		}
		error_message[i] = '\0';	
	}
	~Errors()
	{
		delete []error_message;
	}
	const char* what() const
	{
		return error_message;
	}
};

class Abstract_text
{
public:
   //virtual ~Abstract_text();
	virtual unsigned long int count_symbols() const = 0;
    virtual unsigned long int count_words() const = 0;
    virtual int print(FILE *file) const = 0;
};

class Flags
{
	char filename[256];
	int width;
	int tab;
	char marker;
	int new_line;
	bool file;
public:	
	Flags()
	{
		tab = 8;
		marker = '*';
		new_line = 4;
		file = false;
		struct winsize w;
    	ioctl(0,TIOCGWINSZ, &w);
    	width = w.ws_col; /*По умолчанию ширина равна ширине окна*/
	}
	~Flags()
	{
	}
	char* getname() 
	{
		if (file)
			return filename;
		else
			throw(Errors("You didn't provide a name."));
	}
	void setname(const char* str)
	{
		int i = 0;
		file = true;
		while(str[i])
		{
			filename[i] = str[i];
			i++;
		}	
	}
	int getwidth() const
	{
		return width;
	}
	void setwidth(int i)
	{
		width = i;
	}
	int gettab() const
	{
		return tab;
	}
	void settab(int t)
	{
		tab = t;
	}
	char getmarker() const
	{
		return marker;
	}
	void setmarker(char m)
	{
		marker = m;
	}
	int getnewline() const
	{
		return new_line;
	} 
	void setnewline(int n)
	{
		new_line = n;
	}
	bool there_is_a_filename() const
	{
		return file;
	}
};

class Code: public Abstract_text
{
	char *block;
	int filecount; 
	int it,space;
	int words;
public:
	Code (FILE *file, Flags& flags, char &c)
	{
		filecount = 1024;
		block = new char[filecount];
		parse(file, flags, c);
	}
	~Code()
	{
		delete []block;
	}
	unsigned long int count_symbols() const
	{
		return it;
	}
    unsigned long int count_words() const
    {
    	return words;
    }

	int print (FILE *) const
	{
		for (int i = 0; i < it; i++)
		{
			std::cout << block[i];
		}
		return it;
	}

	int parse(FILE* file, Flags& flags, char &c)
	{
		int end = 0;
		char *tmp;
		it = 0 ;
		int width = 0;
		int word;
		while(!end)
		{
			if (c == ' ' || '\t')
			{
				while (c  == ' ' || c == '\t'){c = fgetc(file);}
			}
			width = 0;
			word = 0;
			block[it]='@';
			it++;
			width++;
			if ((it+1) == filecount)
			{
				tmp = block;
				block = new char [filecount*2];
				for(int f = 0; f < filecount; f++)
				{
					block[f] = tmp[f];
				}
				filecount = filecount * 2;
				delete[] tmp;
			}
			for(int i = 0; i < 3; i++)
			{
				block[it] = ' ';
				it++;
				if ((it+1) == filecount)
				{
					tmp = block;
					block = new char [filecount*2];
					for(int f = 0; f < filecount; f++)
					{
						block[f] = tmp[f];
					}
					filecount = filecount * 2;
					delete[] tmp;
				}
			}
			while(!(width == (flags.getwidth()-4)) && c != '\n')
			{	
				if (c != ' ')
				{
					block[it] = c;
					it++;
					if ((it+1) == filecount)
					{
						tmp = block;
						block = new char [filecount*2];
						for(int f = 0; f < filecount; f++)
						{
							block[f] = tmp[f];
						}
						filecount = filecount * 2;
						delete[] tmp;
					}
					width++;
					word++;
					if (c < 0)
					{
						c = fgetc(file);
						block[it] = c;
						it++;
						if ((it+1) == filecount)
						{
							tmp = block;
							block = new char [filecount*2];
							for(int f = 0; f < filecount; f++)
							{
								block[f] = tmp[f];
							}
							filecount = filecount * 2;
							delete[] tmp;
						}
					}
					c = fgetc(file);
				}
				else 
				{
					word = 0;
					block[it] = c;
					it++;
					if ((it+1) == filecount)
					{
						tmp = block;
						block = new char [filecount*2];
						for(int f = 0; f < filecount; f++)
						{
							block[f] = tmp[f];
						}
						filecount = filecount * 2;
						delete[] tmp;
					}
					words++;
					width++;
					while ((c = fgetc(file)) == ' '){}
				}
			}
			while(c != '\n') {c = fgetc(file);}
			block[it]='\n';
			it++;
			if ((it+1) == filecount)
			{
				tmp = block;
				block = new char [filecount*2];
				for(int f = 0; f < filecount; f++)
				{
					block[f] = tmp[f];
				}
				filecount = filecount * 2;
				delete[] tmp;
			}
			if((c = getc(file)) == '\n') 
			{
				end = 1;
			}

		}
		return it;
	}

};

class Text: public Abstract_text
{
	char *block;
	int filecount; 
	int it,space;
	int words;
public:
	Text (FILE *file, Flags& flags, char &c)
	{
		filecount = 1024;
		block = new char[filecount];
		parse(file, flags, c);
	}
	~Text()
	{
		delete []block;
	}
	unsigned long int count_symbols() const
	{
		return it;
	}
    unsigned long int count_words() const
    {
    	return words;
    }
	int print (FILE *) const
	{
		for (int i = 0; i < it; i++)
		{
			std::cout << block[i];
		}
		return it;
	}
	void resize()
	{
		char* tmp = block;
		block = new char [filecount*2];
		for(int f = 0; f < filecount; f++)
		{
			block[f] = tmp[f];
		}
		filecount = filecount * 2;
		delete[] tmp;
	}
	int parse(FILE* file, Flags& flags, char& c)
	{
		it = 0;
		for (int i = 0; i < flags.getnewline(); i++)
		{
			block[i] = ' ';
			it++;
			if ((it+1) == filecount)
			{
				resize();
			}
		}
		int position = 0;
		int space;
		int end = 0;
		int word = 0;
		int width = 0;
		int tmp_size = 128;
		int tmp_width = flags.getwidth();
		char* tmp = new char[tmp_size];
		tmp_width -=  flags.getnewline();
		while(c != '\n' && c != EOF)
		{
			if (width == tmp_size)
			{
				char *t = tmp;
				tmp = new char[2*tmp_size];
				for(int i = 0; i < tmp_size; i++)
					tmp[i] = t[i];
				delete[] t;
				tmp_size *= 2;
			}
			if ((c != ' ' || width == 0 || tmp[width-1] != ' '))
			{	
				if(tmp[position] == '\t' && (position == 0 || tmp[position-1] != ' '))
				{
					tmp[position] = ' ';
					width++;
				}	
				else
				{
					tmp[width] = c;
					width++;
				}	
			}
			c = fgetc(file);
			if(c == '\n')
			{
				c = fgetc(file);
				if (c != '\n')
				{
					if (width == tmp_size)
					{
						char *t = tmp;
						tmp = new char[2*tmp_size];
						for(int i = 0; i < tmp_size; i++)
							tmp[i] = t[i];
						delete[] t;
						tmp_size *= 2;
					}
					tmp[width] = '\n';
					width++;		
				}
			}

		}
		while(width != position)
		{
			word = 0;
			char* t = new char[2*tmp_width];
			space = 0;
			int current_width = tmp_width;
			int i = position;
			while(current_width && i < width && tmp[i] != '\n')
			{
				if(tmp[i] == ' ' && i == position)
				{
					i++;
					position++;
				}	
				else if (tmp[i] >= 0)
				{
					if(tmp[i] == ' ')
					{ 
						space = i;
						word = 0;
					}
					else word++;	
				 	t[i-position] = tmp[i];
				 	i++;
				 	current_width--;
				}
				else 
				{
					t[i-position] = tmp[i];
				 	t[i+1-position] = tmp[i+1];
					i+=2;
					word++;
					current_width--;
				}				
			}
			if(tmp[i] == '\n')
			{
				for(int k = 0; k < i-position; k++)
				{
					block[it] = t[k];
					it++;
					if ((it+1) == filecount)
					{
						resize();
					}
				}
				
				delete[] t;
				position = i + 1;
			}
			else if (i == width)
			{
				for(int k = 0; k < i-position; k++)
				{
					block[it] = t[k];
					it++;
					if ((it+1) == filecount)
					{
						resize();
					}
				}
				block[it] = '\n';
				it++;
				if ((it+1) == filecount)
				{
					resize();
				}
				delete[] t;
				delete[] tmp;
				break; 
			}
			else if(tmp[i-1] == ' ' || tmp[i] == ' ')
			{
				for(int k = 0; k < i-position; k++)
				{
					block[it] = t[k];
					it++;
					if ((it+1) == filecount)
					{
						resize();
					}
				}
				delete[] t;
				position = i;
				
			}
			else if (word <= 2)
			{
				if (word == 0)
				{
					delete[] t;
					delete[] tmp;
					break;
				}
				if (tmp_width <= 2) 
				{
					delete[] t;
					delete[] tmp;
					throw Errors("not space enougth\0");
				}				
				for(int k = 0; k < space-position; k++)
				{
					if(1)
					{
						block[it] = t[k];
						it++;
						if ((it+1) == filecount)
						{
							resize();
						}
					}	
				}
				for (int k = 0; k <= word; k++)
				{
					block[it] = ' ';
					it++;
					if ((it+1) == filecount)
					{
						resize();
					}
				}
				position = space;
				delete[] t;
			}
			else 
			{
				int test = 0;
				if (t[i-position-2] < 0)
					test = 1;
				for(int k = 0; k < i-position-1-test; k++)
				{
					block[it] = t[k];
					it++;
					if ((it+1) == filecount)
					{
						resize();
					}
				}
				block[it] = '-';
				it++;
				if ((it+1) == filecount)
				{
					resize();
				}
				position = i-1-test;
				delete[] t;
			} 
			block[it] = '\n';
			it++;
			if ((it+1) == filecount)
			{
				resize();
			}
			tmp_width = flags.getwidth();
		}
		block[it] = '\n';
		it++;
		if ((it+1) == filecount)
		{
			resize();
		}		
		return it;
	}
};

class Header: public Abstract_text
{
	char *block;
	int filecount; 
	int it, space;
	int words;
	int marker_count;
	char *tmp;
public:
	Header (FILE *file, Flags& flags, char &c)
	{
		filecount = 1024;
		block = new char[filecount];
		parse(file, flags, c);
	}
	~Header()
	{
		delete[] block;
	}
	unsigned long int count_symbols() const
	{
		return it;
	}
    unsigned long int count_words() const
    {
    	return words;
    }
	int print (FILE *) const
	{
		for (int i = 0; i <= it; i++)
		{
			std::cout << block[i];
		}
		return it;
	}

	void resize()
	{
		tmp = block;
		block = new char [filecount*2];
		for(int f = 0; f < filecount; f++)
		{
			block[f] = tmp[f];
		}
		filecount = filecount * 2;
		delete[] tmp;
	}

	int parse(FILE* file, Flags& flags, char &c)
	{
		int position = 0;
		int space;
		int end = 0;
		int word = 0;
		int tmp_size = 128;
		int width = 0;
		int tmp_width = flags.getwidth();
		char* tmp = new char[tmp_size];
		marker_count = 1;
		c = fgetc(file);
		it = 0;
		if (c == '#')
		{
			marker_count++;
			while ((c = fgetc(file)) == '#')
			{
				marker_count++;
			}
		}
		tmp_width -= 2 * marker_count;
		for (int i = 0; i < flags.getwidth(); i++)
		{
			block[it] = '#';
			it++;
			if ((it+1) == filecount)
			{
				resize();
			}	
		}
		block[it] = '\n';
		it++;
		if ((it+1) == filecount)
		{
			resize();
		}
		while(c != '\n' && c != EOF)
		{
			if (width == tmp_size)
			{
				char *t = tmp;
				tmp = new char[2*tmp_size];
				for(int i = 0; i < tmp_size; i++)
					tmp[i] = t[i];
				delete[] t;
				tmp_size *= 2;
			}
			if ((c != ' ' || width == 0 || tmp[width-1] != ' '))
			{	
				if(tmp[position] == '\t' && (position == 0 || tmp[position-1] != ' '))
				{
					tmp[position] = ' ';
					width++;
				}	
				else
				{
					tmp[width] = c;
					width++;
				}	
			}
			c = fgetc(file);	
		}
		while(width != position)
		{
			word = 0;
			char* t = new char[2*tmp_width];
			space = 0;
			int current_width = tmp_width;
			for(int i = 0; i < marker_count; i++)
			{
				block[it] = '#';
				it++;
				if ((it+1) == filecount)
				{
					resize();
				}
			}
			int i = position;
			while(current_width && i < width)
			{
				if(tmp[i] == ' ' && i == position)
				{
					i++;
					position++;
				}	
				else if (tmp[i] >= 0)
				{
					if(tmp[i] == ' ')
					{ 
						space = i;
						word = 0;
					}
					else word++;	
				 	t[i-position] = tmp[i];
				 	i++;
				 	current_width--;
				}
				else 
				{
					t[i-position] = tmp[i];
				 	t[i+1-position] = tmp[i+1];
					i+=2;
					word++;
					current_width--;
				}
				
			}
			if (i == width)
			{
				int w = current_width / 2;

				for (int k = 0; k < w; k++)
				{
					block[it] = ' ';
					it++;
					if ((it+1) == filecount)
					{
						resize();
					}
				}
				for(int k = 0; k < i-position; k++)
				{
					block[it] = t[k];
					it++;
					if ((it+1) == filecount)
					{
						resize();
					}
				}
				for (int k = 0; k < w +(current_width) % 2; k++)
				{
					block[it] = ' ';
					it++;
					if ((it+1) == filecount)
					{
						resize();
					}
				}	
				for(int k = 0; k < marker_count; k++)
				{
					block[it] = '#';
					it++;
					if ((it+1) == filecount)
					{
						resize();
					}
				}
				block[it] = '\n';
				it++;
				if ((it+1) == filecount)
				{
					resize();
				}
				delete[] t;
				delete[] tmp;
				break; 
			}
			else if(tmp[i-1] == ' ' || tmp[i] == ' ')
			{
				for(int k = 0; k < i-position; k++)
				{
					block[it] = t[k];
					it++;
					if ((it+1) == filecount)
					{
						resize();
					}
				}
				delete[] t;
				position = i;
			}
			else if (word <= 2)
			{
				if (word == 0)
				{
					delete[] t;
					delete[] tmp;
					break;
				}
				if (tmp_width <= 2) 
				{
					delete[] t;
					delete[] tmp;
					throw Errors("not space enougth\0");
				}				
				for (int k = 0; k < (word+1)/2 + (word+1)%2; k++)
				{
					
					block[it] = ' ';
					it++;
					if ((it+1) == filecount)
					{
						resize();
					}
				}
				for(int k = 0; k < space-position; k++)
				{
					if(1)
					{
						block[it] = t[k];
						it++;
						if ((it+1) == filecount)
						{
							resize();
						}
					}	
				}
				for (int k = 0; k < (word+1)/2; k++)
				{
					block[it] = ' ';
					it++;
					if ((it+1) == filecount)
					{
						resize();
					}
				}
				position = space;
				delete[] t;
			}
			else 
			{
				int test = 0;
				if (t[i-position-2] < 0)
					test = 1;
				for(int k = 0; k < i-position-1-test; k++)
				{
					block[it] = t[k];
					it++;
					if ((it+1) == filecount)
					{
						resize();
					}
				}
				block[it] = '-';
				it++;
				if ((it+1) == filecount)
				{
					resize();
				}
				position = i-1-test;
				delete[] t;
			} 
			for(int k = 0; k < marker_count; k++)
			{
				block[it] = '#';
				it++;
				if ((it+1) == filecount)
				{
					resize();
				}
			}
			block[it] = '\n';
			it++;
			if ((it+1) == filecount)
			{
				resize();
			}

		}
		for (int i = 0; i < flags.getwidth(); i++)
		{
			block[it] = '#';
			it++;
			if ((it+1) == filecount)
			{
				resize();
			}
		}
		block[it] = '\n';
		//it++;
		//if ((it+1) == filecount)
		//{
		//	resize();
		//}
		return it;

	}
};

class List: public Abstract_text
{
	char *block;
	int filecount; 
	int it, space;
	int words;
public:
	List (FILE *file, Flags& flags, char &c)
	{
		filecount = 1024;
		block = new char[filecount];
		it = 0;
		parse(file, flags, c);
	}
	~List()
	{
		delete []block;
	}
	unsigned long int count_symbols() const
	{
		return it;
	}
    unsigned long int count_words() const
    {
    	return words;
    }
	int print (FILE *) const
	{
		for (int i = 0; i < it; i++)
		{
			std::cout << block[i];
		}

		return it;
	}
	void resize()
	{
		char *tmp;
		tmp = block;
		block = new char [filecount*2];
		for(int f = 0; f < filecount; f++)
		{
			block[f] = tmp[f];
		}
		filecount = filecount * 2;
		delete[] tmp;
	}
	char* ctoi(int num)
	{
		int i;
		char* tmp = new char[8];
		for(i = 0; i < 8; i++)
		{
			tmp[i] = num % 10 + '0';
			num = num / 10;
			if (num == 0)
				break; 
		}
		char* tmp_tmp = new char[i+2];
		for(int k = 0; k <= i; k++)
			tmp_tmp[k] = tmp[i-k];
		tmp_tmp[i+1] = '\n';
		delete[] tmp;
		return tmp_tmp;	
	}
	void got_number(FILE* file,int num, int spacetab,Flags &flags,char &c)
	{	
		int magic;	
		int tmp_width = flags.getwidth() - spacetab;
		while(c != '.')
		{
			c = fgetc(file);
		}
		c = fgetc(file);
		for (int i = 0; i < spacetab; i++)
		{
			block[it] = ' ';
			it++;
			if(it == filecount)
			{
				resize();
			}
		}
		char* charnum = ctoi(num);
		for(int i = 0; i <= 8; i++)
		{
			block[it] = charnum[i];
			it++;
			if ((it + 1) == filecount)
			{
				resize();
			}
			if (charnum[i+1] == '\n')
			{
				magic = i + 2;
				delete[] charnum;
				break;
			}	
		}
		tmp_width -= magic;
		block[it] = '.';
		it++;
		if ((it+1) == filecount)
		{
			resize();
		}
		int position = 0;
		int space;
		int end = 0;
		int word = 0;
		int width = 0;
		int tmp_size = 128;
		char* tmp = new char[tmp_size];
		tmp_width -=  flags.getnewline();
		while(c != '\n')
		{
			if (width == tmp_size)
			{
				char *t = tmp;
				tmp = new char[2*tmp_size];
				for(int i = 0; i < tmp_size; i++)
					tmp[i] = t[i];
				delete[] t;
				tmp_size *= 2;
			}
			if ((c != ' ' || width == 0 || tmp[width-1] != ' '))
			{	
				if(tmp[position] == '\t' && (position == 0 || tmp[position-1] != ' '))
				{
					tmp[position] = ' ';
					width++;
				}	
				else
				{
					tmp[width] = c;
					width++;
				}	
			}
			c = fgetc(file);
		}
		while(width != position)
		{
			word = 0;
			char* t = new char[2*tmp_width];
			space = 0;
			int current_width = tmp_width;
			int i = position;
			while(current_width && i < width)
			{
				if(tmp[i] == ' ' && i == position)
				{
					i++;
					position++;
				}	
				else if (tmp[i] >= 0)
				{
					if(tmp[i] == ' ')
					{ 
						space = i;
						word = 0;
					}
					else word++;	
				 	t[i-position] = tmp[i];
				 	i++;
				 	current_width--;
				}
				else 
				{
					t[i-position] = tmp[i];
				 	t[i+1-position] = tmp[i+1];
					i+=2;
					word++;
					current_width--;
				}				
			}
			if (i == width)
			{
				for(int k = 0; k < i-position; k++)
				{
					block[it] = t[k];
					it++;
					if ((it+1) == filecount)
					{
						resize();
					}
				}
				block[it] = '\n';
				it++;
				if ((it+1) == filecount)
				{
					resize();
				}
				delete[] t;
				delete[] tmp;
				break; 
			}
			else if(tmp[i-1] == ' ' || tmp[i] == ' ')
			{
				for(int k = 0; k < i-position; k++)
				{
					block[it] = t[k];
					it++;
					if ((it+1) == filecount)
					{
						resize();
					}
				}
				delete[] t;
				position = i;
			}
			else if (word <= 2)
			{
				if (word == 0)
				{
					delete[] t;
					delete[] tmp;
					break;
				}
				if (tmp_width <= 2) 
				{
					delete[] t;
					delete[] tmp;
					throw Errors("not space enougth\0");
				}				
				for(int k = 0; k < space-position; k++)
				{
					if(1)
					{
						block[it] = t[k];
						it++;
						if ((it+1) == filecount)
						{
							resize();
						}
					}	
				}
				for (int k = 0; k <= word; k++)
				{
					block[it] = ' ';
					it++;
					if ((it+1) == filecount)
					{
						resize();
					}
				}
				position = space;
				delete[] t;
			}
			else 
			{
				int test = 0;
				if (t[i-position-2] < 0)
					test = 1;
				for(int k = 0; k < i-position-1-test; k++)
				{
					block[it] = t[k];
					it++;
					if ((it+1) == filecount)
					{
						resize();
					}
				}
				block[it] = '-';
				it++;
				if ((it+1) == filecount)
				{
					resize();
				}
				position = i-1-test;
				delete[] t;
			} 
			block[it] = '\n';
			it++;
			if ((it+1) == filecount)
			{
				resize();
			}
			for(int p = 0; p < spacetab + magic; p++)
			{
				block[it] = ' ';
				it++;
				if ((it+1) == filecount)
				{
					resize();
				}	
			}

		}	
		//c = fgetc(file);	
	}

	void got_marker(FILE* file,int num, int spacetab,Flags &flags,char &c)
	{
	
		int tmp_width = flags.getwidth() - spacetab;
		for (int i = 0; i < spacetab; i++)
		{
			block[it] = ' ';
			it++;
			if(it == filecount)
			{
				resize();
								
			}
		}
		block[it] = flags.getmarker();
		it++;
		if ((it + 1) == filecount)
		{
			resize();
		}
		c = fgetc(file);
		tmp_width--;
		int position = 0;
		int space;
		int end = 0;
		int word = 0;
		int width = 0;
		int tmp_size = 128;
		char* tmp = new char[tmp_size];
		tmp_width -=  flags.getnewline();
		while(c != '\n')
		{
			if (width == tmp_size)
			{
				char *t = tmp;
				tmp = new char[2*tmp_size];
				for(int i = 0; i < tmp_size; i++)
					tmp[i] = t[i];
				delete[] t;
				tmp_size *= 2;
			}
			if ((c != ' ' || width == 0 || tmp[width-1] != ' '))
			{	
				if(tmp[position] == '\t' && (position == 0 || tmp[position-1] != ' '))
				{
					tmp[position] = ' ';
					width++;
				}	
				else
				{
					tmp[width] = c;
					width++;
				}	
			}
			c = fgetc(file);
		}
		while(width != position)
		{
			word = 0;
			char* t = new char[2*tmp_width];
			space = 0;
			int current_width = tmp_width;
			int i = position;
			while(current_width && i < width)
			{
				if(tmp[i] == ' ' && i == position)
				{
					i++;
					position++;
				}	
				else if (tmp[i] >= 0)
				{
					if(tmp[i] == ' ')
					{ 
						space = i;
						word = 0;
					}
					else word++;	
				 	t[i-position] = tmp[i];
				 	i++;
				 	current_width--;
				}
				else 
				{
					t[i-position] = tmp[i];
				 	t[i+1-position] = tmp[i+1];
					i+=2;
					word++;
					current_width--;
				}				
			}
			if (i == width)
			{
				for(int k = 0; k < i-position; k++)
				{
					block[it] = t[k];
					it++;
					if ((it+1) == filecount)
					{
						resize();
					}
				}
				block[it] = '\n';
				it++;
				if ((it+1) == filecount)
				{
					resize();
				}
				delete[] t;
				delete[] tmp;
				break; 
			}
			else if(tmp[i-1] == ' ' || tmp[i] == ' ')
			{
				for(int k = 0; k < i-position; k++)
				{
					block[it] = t[k];
					it++;
					if ((it+1) == filecount)
					{
						resize();
					}
				}
				delete[] t;
				position = i;
			}
			else if (word <= 2)
			{
				if (word == 0)
				{
					delete[] t;
					delete[] tmp;
					break;
				}
				if (tmp_width <= 2) 
				{
					delete[] t;
					delete[] tmp;
					throw Errors("not space enougth\0");
				}				
				for(int k = 0; k < space-position; k++)
				{
					if(1)
					{
						block[it] = t[k];
						it++;
						if ((it+1) == filecount)
						{
							resize();
						}
					}	
				}
				for (int k = 0; k <= word; k++)
				{
					block[it] = ' ';
					it++;
					if ((it+1) == filecount)
					{
						resize();
					}
				}
				position = space;
				delete[] t;
			}
			else 
			{
				int test = 0;
				if (t[i-position-2] < 0)
					test = 1;
				for(int k = 0; k < i-position-1-test; k++)
				{
					block[it] = t[k];
					it++;
					if ((it+1) == filecount)
					{
						resize();
					}
				}
				block[it] = '-';
				it++;
				if ((it+1) == filecount)
				{
					resize();
				}
				position = i-1-test;
				delete[] t;
			} 
			block[it] = '\n';
			it++;
			if ((it+1) == filecount)
			{
				resize();
			}
			for(int p = 0; p <= spacetab; p++)
			{
				block[it] = ' ';
				it++;
				if ((it+1) == filecount)
				{
					resize();
				}	
			}
		}
		//c = fgetc(file);
	}

	int parse(FILE* file, Flags& flags, char &c)
	{ 
		int spacetab = 0;
		int i = 0;
		while (c != EOF)
		{
			if (c == '*')
			{
				got_marker(file, 0, spacetab, flags, c);
				i = 0;
			}
			else if (c < '9' && c >'0')
			{
				i++;
				got_number(file, i, spacetab, flags, c);
			}
			spacetab = 0;
			c = fgetc(file);
			if (c == '\n')
			{
				break;
			}
			if (c == ' ')
			{
				spacetab++;
				while(c == ' ')
				{
					c = fgetc(file);
					spacetab++;
				}
			}
		}
		return it;
	}


};

class Blocks
{
	Abstract_text **text;
	int block_count;
	int block_count_end;
public:
	Blocks()
	{
		block_count = 0;
		text = new Abstract_text*[8];
		block_count_end = 8;
	}
	~Blocks()
	{

		delete[] text;
	}

	void add_block(Abstract_text *a)
	{
		Abstract_text **tmp;
		if(!(block_count < block_count_end))
		{
			tmp = text;
			text = new Abstract_text* [block_count_end*2];
			for (int i = 0; i <= block_count_end; i++)
			{
				text[i] = tmp[i];
			}
			delete[] tmp;
			block_count_end = block_count_end * 2; 
		}
		text[block_count] = a; 
		block_count++;
	}
	Abstract_text* operator[](int n) const
	{
		if ((n >= 0) && (n <= block_count))
		{
			return text[n];
		}
		else 
		{
			throw(Errors("no such element in text"));
		}
	} 
};

class Text_viewer
{
	Flags flags;
	Blocks blocks; 
	FILE *file;
	int iterator;

	char** arguments;
	int arg_count;	
	const char* help_message;
public:
	Text_viewer(char* a[], int c): arguments(a), arg_count(c) 
	{
		help_message = "\
		1. -f имя файла с разметкой\n\
		2. -w ширина экрана\n\
		3. -t отступ для второй и последующих строк списка\n\
		4. -m символ-маркер ненумерованного списка,\n\
		5. -r величина красной строки\n\
		6. -h выдача help с описанием поведения программы\n\
		7. -v отображение версии программы\
		";
		set_arguments();
		iterator = read_text();
	}
	~Text_viewer()
	{

	}
	int read_text()
	{
		int it = 0;
		char c;
		int block_count=0;
		file = fopen(flags.getname(), "r");
		

		while (c != EOF)
		{
			c = fgetc(file);
			if (c == '\n')
			{
				c = fgetc(file);
			}
			if(c == EOF) break;
			else if(c == '#')
			{
				Header tmp(file, flags, c);
				tmp.print(file);
				blocks.add_block(&tmp);
				block_count++;

			}
			else if (c == ' ' || c == '\t')
			{
				Code tmp(file, flags, c);
				tmp.print(file);
				blocks.add_block(&tmp);
				block_count++;

			}
			else if ((c >= '0' && c <= '9') || c == '*')
			{
				List tmp(file, flags, c);
				tmp.print(file);
				blocks.add_block(&tmp);
				block_count++;
			}
			else if (c != '#' && (c < '0' || c > '9') && c != '*' && c != '\n')
			{
				Text tmp(file, flags, c);
				tmp.print(file);
				blocks.add_block(&tmp);
				block_count++;
			}
		}
		fclose(file);
		return it;
	}
	void set_arguments()
	{
		int c;
		while ((c = getopt(arg_count, arguments, "v:f:w:t:m:r:h")) != -1)
		{
			switch (c)
			{
				case('h'): std::cout << help_message << std::endl; throw(0);
				case('v'): std::cout << VER << std::endl; throw(0);
				case('f'): flags.setname(optarg); break; 
				case('w'): flags.setwidth(atoi(optarg)); break;
				case('t'): flags.settab(atoi(optarg)); break;
				case('m'): flags.setmarker(optarg[0]); break;
				case('r'): flags.setnewline(atoi(optarg)); break;
				default: throw(Errors("Wrong argument")); break;
			}	
		}
		if(!flags.there_is_a_filename())
		throw(Errors("There is no file specified."));
	}	
};



int main(int argc, char *argv[])
{
	try
	{
		Text_viewer a(argv, argc);
	}
	catch(Errors &err)
	{
		std::cerr << err.what() << std::endl;
	}
	catch(...){};
	return 0;
}