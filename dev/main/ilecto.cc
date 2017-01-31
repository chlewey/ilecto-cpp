
#include "interlecto.h"

using namespace web;

int web::main(enviro&Enviro) {
	content Content(Enviro);
	format Page(Enviro);

	string request(Enviro.value("request"));
	trim(request,"\\/");
	Page.set_title(request);
	Page.load(Content);

	cout << Enviro.headers();
	cout << Page.html();

	return Enviro.status();
}

htmlcode* web::make_content(content&Content) {
	NEWPTR(html::block,cp)("div","content");
	info*Env = Content["enviro"];
	cp->append(Content.value("page:title"),"h1");

	info*Serv = Env->at("server");
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
