

#include "interlecto.h"

using namespace web;

int web::main(enviro&Enviro) {
	content Content(Enviro);
	format Page(Enviro);

	Page.set_title("Hello, World!");
	Page.load(Content);

	cout << Enviro.headers();
	cout << Page.html();

	return Enviro.status();
}

htmlcode* web::make_content(content&Content) {
	NEWPTR(html::block,cp)("div","content");
	cp->append("Hello, World", "h1");
	cp->append("Lorem ipsum, dolor sit amnet...");
	
	info*Env = Content["enviro"];
	info*Serv = Env->at("server");
	
	cp->append("GET Form", "h2");
	NEWPTR(html::form,f1)("get");
	NEWPTR(html::par,p1_1)("div");
	p1_1->append( new html::label("f1_fname","First Name") );
	p1_1->append( new html::input("f1_fname","first_name",Env->value("get:first_name")) );
	f1->append(p1_1);
	NEWPTR(html::par,p1_2)("div");
	p1_2->append( new html::label("f1_lname","Last Name") );
	p1_2->append( new html::input("f1_lname","last_name",Env->value("get:last_name")) );
	f1->append(p1_2);
	NEWPTR(html::par,p1_3)("div");
	p1_3->append( new html::submit("Send GET") );
	f1->append(p1_3);
	cp->append(f1);
	
	cp->append("POST Form", "h2");
	NEWPTR(html::form,f2)("post");
	NEWPTR(html::par,p2_1)("div");
	p2_1->append( new html::label("f2_fname","First Name") );
	p2_1->append( new html::input("f2_fname","first_name",Env->value("post:first_name")) );
	f2->append(p2_1);
	NEWPTR(html::par,p2_2)("div");
	p2_2->append( new html::label("f2_lname","Last Name") );
	p2_2->append( new html::input("f2_lname","last_name",Env->value("post:last_name")) );
	f2->append(p2_2);
	NEWPTR(html::par,p2_3)("div");
	p2_3->append( new html::submit("Send POST") );
	f2->append(p2_3);
	cp->append(f2);

	cp->append("Variables", "h2");
	cp->append("GET variables", "h3");
	if(Env->key_exists("get")) {
		info*Get = Env->at("get");
		NEWPTR(html::table,tab2);
		for(auto x: *Get) {
			NEWPTR(html::tr_comp,tr2);
			tr2->append(new html::td_comp(x.first));
			tr2->append(new html::td_comp(x.second->value() ));
			tab2->append(tr2);
		}
		cp->append(tab2);
	}
	if(Env->key_exists("get_query")) {
		cp->append(Env->at("get_query")->value());
	}

	cp->append("POST variables", "h3");
	if(Env->key_exists("post")) {
		info*Post = Env->at("post");
		NEWPTR(html::table,tab3);
		for(auto x: *Post) {
			NEWPTR(html::tr_comp,tr3);
			tr3->append(new html::td_comp(x.first));
			tr3->append(new html::td_comp(x.second->value() ));
			tab3->append(tr3);
		}
		cp->append(tab3);
	}
	if(Env->key_exists("post_len")) {
		cp->append(Env->at("post_len")->value());
	}
	if(Env->key_exists("post_query")) {
		cp->append(Env->at("post_query")->value());
	}
	
	cp->append("Environmental vars", "h2");
	NEWPTR(html::table,tab);
	for(auto x: *Serv) {
		NEWPTR(html::tr_comp,tr1);
		tr1->append(new html::td_comp(x.first));
		tr1->append(new html::td_comp(x.second->value() ));
		tab->append(tr1);
	}
	cp->append(tab);

	return cp;
}
