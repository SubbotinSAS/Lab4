#include <iostream>
#include <fstream>
#include <vector>
//#include <stdio.h>
#include <cstring>
#include <string>
#include <dirent.h>
#include <list>
#include <iterator>

using namespace std;

struct IFF{
private:
	int count=0;
    int pos;
    string cap;
    string body;
public:

    void ifcheck(string &s){
        char ss[s.length()];
        for (int i = 0; i<s.length();i++){
            ss[i] = s[i];
        }
        if (strchr(ss,'(')-ss>-1 && strchr(ss,')')-ss>-1) {
            int t = strchr(ss,'(')-ss+1;
            while (ss[t] != ')'){
                cap += ss[t];
                t++;
            }
            pos=t;
        }
    }

    void write(int &nn,string &s,int &ty){
        while(s[0]==' '){s.erase(0,1);}
        for(int t = 0; t<s.length();t++){
            if(s[t]=='\r'){s.erase(t,1);}
            if(s[t]=='\n'){s.erase(t,1);}
        }
        char ss[s.length()+1];
        for (int i = 0; i<s.length();i++){
            ss[i] = s[i];
        }
        if(nn == 3 && ty==1){
            for (int i = pos;i<s.length();i++){
                if(s[i]==';'){body+=s[i];nn=0;count++;}
                if(nn==3){body+=s[i];}
            }
        }
        if(nn == 3 && ty==0){
            for (int i = 0;i<s.length();i++){
                if(s[i]==';'){body+=s[i];nn=0;count++;}
                if(nn==3){body+=s[i];}
            }
        }
        if(nn == 4 && ty==1){
            for(int i = 0;i<s.length();i++){
                if(s[i]=='{'){pos=i;}
            }
            for(int i = pos+1;i<s.length();i++){
                if(nn==4 && s[i]=='}'){body+=s[i];nn=0;}
				if(nn==4 && s[i]==';'){count++;}
                if(nn==4){body+=s[i];}
            }
        }
        if(nn==4 && ty==0){
            for(int i = 0;i<s.length();i++){
                if(nn==4 && s[i]=='}'){nn=0;}
				if(nn==4 && s[i]==';'){count++;}
                if(nn==4){body+=s[i];}
            }
        }
    }

    string get(ofstream &out,string &container){
        cout<<cap<<endl;
        out<<"Условие if:   "+cap<<endl;
		container+=cap;
        cout<<body<<endl;
        out<<"Тело if:   "+body<<endl;
		container+=body;
		out<<"if содержит  ";out<<count;out<<"   точек с запятой"<<endl;
		cap.erase();
		body.erase();
		count=0;
        return cap;
        return body;
    }
};

struct Forr{
private:
	int count=0;
    int pos;
    string pre;
    string inn;
    string aft;
    string body;
public:

    void check(string &s){
        char ss[s.length()];
        for (int i = 0; i<s.length();i++){
            ss[i] = s[i];
        }
        if (strchr(ss,'(')-ss>-1 && strchr(ss,')')-ss>-1) {
            int i = strchr(ss,'(')-ss+1;
            while (ss[i] != ';' && ss[i] != '('){
                pre += ss[i];
                i++;
            }
            if (ss[i] == ';') {
                i++;
            }
            while (ss[i] != ';'){
                inn += ss[i];
                i++;
            }
            if (ss[i] == ';') {
                i++;
            }
            while (ss[i] != ')'){
                aft += ss[i];
                i++;
            }
            pos=i;
        }
    }

    void write(int &nn,string &s,int &ty){
        while(s[0]==' '){s.erase(0,1);}
        for(int t = 0; t<s.length();t++){
            if(s[t]=='\r'){s.erase(t,1);}
            if(s[t]=='\n'){s.erase(t,1);}
        }
        char ss[s.length()];
        for (int i = 0; i<s.length();i++){
            ss[i] = s[i];
        }
        if(nn == 1 && ty==1){
            for (int i = pos;i<s.length();i++){
                if(s[i]==';'){body+=s[i];nn=0;count++;}
                if(nn==1){body+=s[i];}
            }
        }
        if(nn == 1 && ty==0){
            for (int i = 0;i<s.length();i++){
                if(s[i]==';'){body+=s[i];nn=0;count++;}
                if(nn==1){body+=s[i];}
            }
        }
        if(nn == 2 && ty==1){
            for(int i = 0;i<s.length();i++){
                if(s[i]=='{'){pos=i;}
            }
            for(int i = pos+1;i<s.length();i++){
                if(nn==2 && s[i]=='}'){/*body+=s[i];*/nn=0;}
                if(nn==2 && s[i]!='}'){body+=s[i];}
				if(nn==2 && s[i]==';'){count++;}
            }
        }
        if(nn==2 && ty==0){
            for(int i = 0;i<s.length();i++){
                if(nn==2 && s[i]=='}'){nn=0;}
                if(nn==2 && s[i]!='}'){body+=s[i];}
				if(nn==2 && s[i]==';'){count++;}
            }
        }
    }

    string get(ofstream &out,string &container){
        cout<<pre<<endl;
        out<<"Первый блок for:   "+pre<<endl;
		container+=pre;
        cout<<inn<<endl;
        out<<"Второй блок for:   "+inn<<endl;
		container+=inn;
        cout<<aft<<endl;
        out<<"Третий блок for:   "+aft<<endl;
		container+=aft;
        cout<<body<<endl;
        out<<"Тело for:   "+body<<endl;
		container+=body;
		out<<"for содержит  ";out<<count;out<<"  точек с запятой"<<endl;
		pre.erase();inn.erase();aft.erase();body.erase();count=0;
        return pre;
        return inn;
        return aft;
        return body;
    }
};

struct switt{
private:
	int count=0;
    int pos;
    int t=0;
    string in;
    string prom;
    vector <string> cases;
    vector <string> incas;
public:
    void check(string &s){
        char ss[s.length()];
        for (int i = 0; i<s.length();i++){
            ss[i] = s[i];
        }
        if (strchr(ss,'(')-ss>-1 && strchr(ss,')')-ss>-1) {
            int t = strchr(ss,'(')-ss+1;
            while (ss[t] != ')'){
                in += ss[t];
                t++;
            }
            pos=t;
        }
    }
    void write(int &nn,string &s,int &ty){
        //while(s[0]==' '){s.erase(0,1);}
        for(int t = 0; t<s.length();t++){
            if(s[t]=='\r'){s.erase(t,1);}
            if(s[t]=='\n'){s.erase(t,1);}
        }
        if(ty==1) {
            for (int i = 0; i < s.length(); i++) {
                if(s[i]=='{'){pos=i;}
            }
            for (int i = pos;i<s.length();i++) {
                if (t == 1 && s[i] == 'd' && s[i + 1] == 'e' && s[i + 2] == 'f' && s[i + 3] == 'a' && s[i + 4] == 'u' &&
                    s[i + 5] == 'l' && s[i + 6] == 't' && s[i + 7] == ' ') {
                    if (s[i - 1] == ' ' || s[i - 1] == '(' || s[i - 1] == '{' || s[i - 1] == ';' || s[i - 1] == ':' ||
                        s[i - 1] == '}' || s[i - 1] == ')' || s[i - 1] == '[' || s[i - 1] == ']' || s[i - 1] == '&' ||
                        s[i - 1] == '|' || s[i - 1] == '	') {
                        incas.push_back(prom);
                        prom.erase();
                        while (s[i] != ':') {
                            prom += s[i];
                            i++;
                        }
                        prom += ':';
                        cases.push_back(prom);
                        prom.erase();
                        t = 2;
                    }
                }
                if (t == 1 && s[i] == 'd' && s[i + 1] == 'e' && s[i + 2] == 'f' && s[i + 3] == 'a' && s[i + 4] == 'u' &&
                    s[i + 5] == 'l' && s[i + 6] == 't' && s[i + 7] == ':') {
                    if (s[i - 1] == ' ' || s[i - 1] == '(' || s[i - 1] == '{' || s[i - 1] == ';' || s[i - 1] == ':' ||
                        s[i - 1] == '}' || s[i - 1] == ')' || s[i - 1] == '[' || s[i - 1] == ']' || s[i - 1] == '&' ||
                        s[i - 1] == '|' || s[i - 1] == '	') {
                        incas.push_back(prom);
                        prom.erase();
                        while (s[i] != ':') {
                            prom += s[i];
                            i++;
                        }
                        prom += ':';
                        cases.push_back(prom);
                        prom.erase();
                        t = 2;
                    }
                }
                if (t == 1 && s[i] == 'c' && s[i + 1] == 'a' && s[i + 2] == 's' && s[i + 3] == 'e' && s[i + 4] == ' ') {
                    if (s[i - 1] == ' ' || s[i - 1] == '(' || s[i - 1] == '{' || s[i - 1] == ';' || s[i - 1] == ':' ||
                        s[i - 1] == '}' || s[i - 1] == ')' || s[i - 1] == '[' || s[i - 1] == ']' || s[i - 1] == '&' ||
                        s[i - 1] == '|' || s[i - 1] == '	') {
                        incas.push_back(prom);
                        prom.erase();
                        while (s[i] != ':') {
                            prom += s[i];
                            i++;
                        }
                        prom += ':';
                        cases.push_back(prom);
                        prom.erase();
                        t = 1;
                    }
                }
                if (t == 0 && s[i] == 'c' && s[i + 1] == 'a' && s[i + 2] == 's' && s[i + 3] == 'e' && s[i + 4] == ' ') {
                    if (s[i - 1] == ' ' || s[i - 1] == '(' || s[i - 1] == '{' || s[i - 1] == ';' || s[i - 1] == ':' ||
                        s[i - 1] == '}' || s[i - 1] == ')' || s[i - 1] == '[' || s[i - 1] == ']' || s[i - 1] == '&' ||
                        s[i - 1] == '|' || s[i - 1] == '	') {
                        while (s[i] != ':') {
                            prom += s[i];
                            i++;
                        }
                        prom += ':';
                        cases.push_back(prom);
                        prom.erase();
                        t = 1;
                    }
                }
                if (t == 1 && s[i] != ':' && s[i] != '}') {
					if(s[i]==';'){count++;}
                    prom += s[i];
                }
                if (t == 2 && s[i] != ':' && s[i] != '}') {
					if(s[i]==';'){count++;}
                    prom += s[i];
                }
                if (t == 2 && s[i] == '}') {
                    t = 3;
                    incas.push_back(prom);
                    prom.erase();
                }
            }
        }
        if(ty==0){
            for(int i=0;i<s.length();i++){
                if (t == 1 && s[i] == 'd' && s[i + 1] == 'e' && s[i + 2] == 'f' && s[i + 3] == 'a' && s[i + 4] == 'u' &&
                    s[i + 5] == 'l' && s[i + 6] == 't' && s[i + 7] == ' ') {
                    if (s[i - 1] == ' ' || s[i - 1] == '(' || s[i - 1] == '{' || s[i - 1] == ';' || s[i - 1] == ':' ||
                        s[i - 1] == '}' || s[i - 1] == ')' || s[i - 1] == '[' || s[i - 1] == ']' || s[i - 1] == '&' ||
                        s[i - 1] == '|' || s[i - 1] == '	') {
                        incas.push_back(prom);
                        prom.erase();
                        while (s[i] != ':') {
                            prom += s[i];
                            i++;
                        }
                        prom += ':';
                        cases.push_back(prom);
                        prom.erase();
                        t = 2;
                    }
                }
                if (t == 1 && s[i] == 'd' && s[i + 1] == 'e' && s[i + 2] == 'f' && s[i + 3] == 'a' && s[i + 4] == 'u' &&
                    s[i + 5] == 'l' && s[i + 6] == 't' && s[i + 7] == ':') {
                    if (s[i - 1] == ' ' || s[i - 1] == '(' || s[i - 1] == '{' || s[i - 1] == ';' || s[i - 1] == ':' ||
                        s[i - 1] == '}' || s[i - 1] == ')' || s[i - 1] == '[' || s[i - 1] == ']' || s[i - 1] == '&' ||
                        s[i - 1] == '|' || s[i - 1] == '	') {
                        incas.push_back(prom);
                        prom.erase();
                        while (s[i] != ':') {
                            prom += s[i];
                            i++;
                        }
                        prom += ':';
                        cases.push_back(prom);
                        prom.erase();
                        t = 2;
                    }
                }
                if (t == 1 && s[i] == 'c' && s[i + 1] == 'a' && s[i + 2] == 's' && s[i + 3] == 'e' && s[i + 4] == ' ') {
                    if (s[i - 1] == ' ' || s[i - 1] == '(' || s[i - 1] == '{' || s[i - 1] == ';' || s[i - 1] == ':' ||
                        s[i - 1] == '}' || s[i - 1] == ')' || s[i - 1] == '[' || s[i - 1] == ']' || s[i - 1] == '&' ||
                        s[i - 1] == '|' || s[i - 1] == '	') {
                        incas.push_back(prom);
                        prom.erase();
                        while (s[i] != ':') {
                            prom += s[i];
                            i++;
                        }
                        prom += ':';
                        cases.push_back(prom);
                        prom.erase();
                        t = 1;
                    }
                }
                if (t == 0 && s[i] == 'c' && s[i + 1] == 'a' && s[i + 2] == 's' && s[i + 3] == 'e' && s[i + 4] == ' ') {
                    if (s[i - 1] == ' ' || s[i - 1] == '(' || s[i - 1] == '{' || s[i - 1] == ';' || s[i - 1] == ':' ||
                        s[i - 1] == '}' || s[i - 1] == ')' || s[i - 1] == '[' || s[i - 1] == ']' || s[i - 1] == '&' ||
                        s[i - 1] == '|' || s[i - 1] == '	') {
                        while (s[i] != ':') {
                            prom += s[i];
                            i++;
                        }
                        prom += ':';
                        cases.push_back(prom);
                        prom.erase();
                        t = 1;
                    }
                }
                if (t == 1 && s[i] != ':' && s[i] != '}') {
					if(s[i]==';'){count++;}
                    prom += s[i];
                }
                if (t == 2 && s[i] != ':' && s[i] != '}') {
					if(s[i]==';'){count++;}
                    prom += s[i];
                }
                if (t == 2 && s[i] == '}') {
                    t = 3;
                    incas.push_back(prom);
                    prom.erase();
                    nn=0;
                }
            }
        }
    }

    string get(ofstream &out,string &container){
        cout<<in<<endl;
		container+=in;
        out<<"Условие switch:   "+in<<endl;
        for(int i=0;i<incas.size();i++) {
            cout << cases[i]<<endl;
			container+=cases[i];
            cout<< incas[i] << endl;
			container+=incas[i];
            out<<cases[i]+"  "+incas[i]<<endl;
        }
		out<<"switch содержит  ";out<<count;out<<"  точек с запятой"<<endl;
		for(int i=0;i<incas.size();i++) {
		cases.pop_back();
		incas.pop_back();
		}
		in.erase();count=0;
        return in;
    }
};

int main(void) {
	list <string> data;
	list <string> :: iterator it;
	string container;
	string line;
	string lline = "  ";
    DIR *dir;
    struct dirent *ent;
    if((dir = opendir("C:/1/Lab4/files"))!=NULL){
        while((ent=readdir(dir))!=NULL) {
			printf("%s\n", ent->d_name);
			string file = ent->d_name;
			string o_file = "o_" + file;
			int nn = 0;
			int nnn = 0;
			int tt = 0;
			int t = 0;
			int tc = 0;
			int ty;
			IFF qq;
			Forr rew;
			switt dd;
			string llline;
			string lllline;
			ifstream in("C:/1/Lab4/files/" + file);
			ofstream out("C:/1/Lab4/o.files/" + o_file, ios_base::out);
			if (in.is_open() && out.is_open()) {
				while (getline(in, line)) {
					lline = "  ";
					lline += line;

					for (int i = 0; i < lline.length(); i++) {
						if (nn != 5 && nn != 6 && lline[i - 1] == ' ' && lline[i] == 'f' && lline[i + 1] == 'o' &&
							lline[i + 2] == 'r' && lline[i + 3] == '(') {
							rew.check(lline);
							nn = 1;
							ty = 1;
						}
						if (nn != 5 && nn != 6 && lline[i - 1] == ' ' && lline[i] == 'f' && lline[i + 1] == 'o' &&
							lline[i + 2] == 'r' && lline[i + 3] == ' ') {
							rew.check(lline);
							nn = 1;
							ty = 1;
						}
						if (nn == 1 && lline[i] == '{') {
							nn = 2;
							ty = 1;
						}
						if (lline[i - 1] == ' ' && lline[i] == 'i' && lline[i + 1] == 'f' && lline[i + 2] == '(') {
							qq.ifcheck(lline);
							nn = 3;
							ty = 1;
						}
						if (lline[i - 1] == ' ' && lline[i] == 'i' && lline[i + 1] == 'f' && lline[i + 2] == ' ') {
							qq.ifcheck(lline);
							nn = 3;
							ty = 1;
						}
						if (nn == 3 && lline[i] == '{') {
							nn = 4;
							ty = 1;
						}
						if (lline[i - 1] == ' ' && lline[i] == 's' && lline[i + 1] == 'w' && lline[i + 2] == 'i' &&
							lline[i + 3] == 't' && lline[i + 4] == 'c' && lline[i + 5] == 'h' && lline[i + 6] == ' ') {
							dd.check(lline);
							nn = 5;
							ty = 1;
						}
						if (lline[i - 1] == ' ' && lline[i] == 's' && lline[i + 1] == 'w' && lline[i + 2] == 'i' &&
							lline[i + 3] == 't' && lline[i + 4] == 'c' && lline[i + 5] == 'h' && lline[i + 6] == '(') {
							dd.check(lline);
							nn = 5;
							ty = 1;
						}
						if (nn == 5 && lline[i] == '{') {
							nn = 6;
							ty = 1;
						}
					}


					if (nn == 1 || nn == 2) {
						rew.write(nn, lline, ty);
					}
					if (nn == 3 || nn == 4) {
						qq.write(nn, lline, ty);
					}
					if (nn == 5 || nn == 6) {
						dd.write(nn, lline, ty);
					}
					llline += line;
					ty = 0;
				}

				int pos1;
				int pos2;
				int t_co=0;
				for(int i=0;i<llline.length();i++){
					//if(llline[i]=='	'){llline.erase(i,1);i=i-1;}
					if(llline[i]=='{'){t_co=0;pos1=i;}
					if(llline[i]==';'){t_co++;}
					if(llline[i]=='}' && i!=llline.length()-1){pos2=i;if(t_co==1){llline.erase(pos1,1);llline.erase(pos2-1,1);}t_co=0;/*i=i-2;*/}
				}
			for (int i = 0; i < llline.length(); i++) {
				lllline += llline[i];
				if (nnn == 0 && llline[i] == '>') {
					out << lllline << endl;
					lllline.erase();
				}
				if (llline[i] == ';' || llline[i] == '(' || llline[i] == '{') {
					nnn = 1;
				}
				if (nnn == 1 && llline[i] == '(') {
					t = 1;
				}
				if (nnn == 1 && llline[i] == '{') {
					for (int y = 0; y < tc; y++) {
						out << "    ";
					}
					out << lllline << endl;
					lllline.erase();
					tc = tc + 1;
				}
				if (nnn == 1 && llline[i] == ';' && t == 0 && tt == 0) {
					for (int y = 0; y < tc; y++) {
						out << "    ";
					}
					out << lllline << endl;
					lllline.erase();
				}
				if (nnn == 1 && llline[i] == ';' && t == 0 && tt == 1) {
					for (int y = 0; y < tc; y++) {
						out << "    ";
					}
					tc = tc - 1;
					tt = 0;
					out << lllline << endl;
					lllline.erase();
				}
				if (nnn == 1 && llline[i] == ')') {
					while (llline[i + 1] == ' ') {
						llline.erase(i + 1, 1);
					}
					t = 0;
				}
				if (nnn == 1 && llline[i] == ')' && llline[i + 1] != ',' && llline[i + 1] != ';' && llline[i + 1] != '{') {
					for (int y = 0; y < tc; y++) {
						out << "    ";
					}
					out << lllline << endl;
					lllline.erase();
					tt = 1;
					tc = tc + 1;
				}
				if (nnn == 1 && llline[i] == '}') {
					tc = tc - 1;
					for (int y = 0; y < tc; y++) {
						out << "    ";
					}
					out << lllline << endl;
					lllline.erase();
				}
			}
				rew.get(out,container);
				qq.get(out,container);
				dd.get(out,container);
				cout<<"ok"<<endl;
				data.push_back(container);
				container.erase();
		}
			else
				cout<<"Error!"<<endl;

			in.close();
        }
        closedir(dir);
    }else{
        perror("");
        return EXIT_FAILURE;
    }
	for(it=data.begin();it!=data.end();it++){cout<<(*it)<<"    ";}
    return 0;
}
