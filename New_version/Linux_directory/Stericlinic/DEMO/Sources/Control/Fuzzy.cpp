/*
 * Fuzzy.cpp
 *
 *  Created on: Aug 25, 2016
 *      Author: Holguer
 */

#include "Fuzzy.h"
#include "ffll/expr.h"
#include "ffll/op.h"
#include "ffll/value.h"
#include "ffll/coreutils.h"

using namespace expr;
using namespace std;
using namespace op;
using namespace value;
using namespace coreutils;

void Fuzzy::testOp() {
	/* Test Value */
	ValueModel<float> *vm1 = new ValueModel<float>(3);
	ValueModel<float> *vm2 = new ValueModel<float>(39);

	printf("Eval1 %f\n", vm1->evaluate());
	printf("Eval2 %f\n", vm2->evaluate());

	/* Test Operator */
	AggMax<float>* aggmax = new AggMax<float>();
	AggPlus<float>* aggplus = new AggPlus<float>();
	AndMin<float>* andmin = new AndMin<float>();
	AndMult<float>* andmult = new AndMult<float>();
	//CogDefuzz<float>* cogdefuzz = new CogDefuzz<float>();
	NotMinus1<float>* notminus1 = new NotMinus1<float>();
	OrMax<float>* ormax = new OrMax<float>();
	OrPlus<float>* orplus = new OrPlus<float>();
	//SugenoDefuzz<float>* sugenodefuzz = new SugenoDefuzz<float>();
	ThenMin<float>* thenmin = new ThenMin<float>();
	ThenMult<float>* thenmult = new ThenMult<float>();

	BinaryExpressionModel<float> a(vm1, vm2, aggmax);
	printf("Eval %f\n", a.evaluate());
	BinaryExpressionModel<float> b(vm1, vm2, aggplus);
	printf("Eval %f\n", b.evaluate());
	BinaryExpressionModel<float> c(vm1, vm2, andmin);
	printf("Eval %f\n", c.evaluate());
	BinaryExpressionModel<float> d(vm1, vm2, andmult);
	printf("Eval %f\n", d.evaluate());
	UnaryExpressionModel<float> e(vm1, notminus1);
	printf("Eval %f\n", e.evaluate());
	BinaryExpressionModel<float> j(vm1, vm2, ormax);
	printf("Eval %f\n", j.evaluate());
	BinaryExpressionModel<float> g(vm1, vm2, orplus);
	printf("Eval %f\n", g.evaluate());
	BinaryExpressionModel<float> h(vm1, vm2, thenmin);
	printf("Eval %f\n", h.evaluate());
	BinaryExpressionModel<float> i(vm1, vm2, thenmult);
	printf("Eval %f\n", i.evaluate());
	//BinaryExpressionModel<float> j(vm1, vm2, orplus);
	//cout << j.evaluate() << endl;

	delete vm1;
	delete vm2;
	delete orplus;
}

void Fuzzy::testTriangle() {
	printf("Test Triangle");

	//Is
	IsTriangle<float> tri = IsTriangle<float>(119, 121, 123);
	ValueModel<float> vm = ValueModel<float>(0);
	UnaryExpressionModel<float> expr = UnaryExpressionModel<float>(&vm, &tri);

	float s;
	while (true) {
		printf("Ingrese Temperatura Medida:");
		scanf("%f", &s);
		vm.setValue(s);
		printf("Resultado para setear al pwm del MOSFET %f\n",
				128 - expr.evaluate() * 128);
	}

}

void Fuzzy::testMamdani() {
	//utils
	Interval<float> interval = Interval<float>(5, 25, 1);

	//operators
	NotMinus1<float> opNot;
	AndMin<float> opAnd;
	OrMax<float> opOr;
	ThenMin<float> opThen;
	AggMax<float> opAgg;
	CogDefuzz<float> opMamdani = CogDefuzz<float>(&interval);
	SugenoDefuzz<float> opSugeno = SugenoDefuzz<float>();

	vector<float> coef;
	coef.push_back(1);
	coef.push_back(1);
	SugenoConclusion<float> opConclusion = SugenoConclusion<float>(&coef);

	//fuzzy expession factory
	FuzzyFactory<float> f(&opNot, &opAnd, &opOr, &opThen, &opAgg, &opMamdani,
			&opSugeno, &opConclusion);

	//membership function
	IsTriangle<float> poor(-5, 0, 119);
	IsTriangle<float> good(119, 120, 121);
	IsTriangle<float> excellent(120, 121, 122);
	IsTriangle<float> cheap(0, 118, 10);
	IsTriangle<float> average(119, 121, 123);
	IsTriangle<float> generous(121, 121, 121);

	//values
	ValueModel<float> service(0);
	ValueModel<float> tips(0);

	Expression<float> *r = f.newAgg(
			f.newAgg(
					f.newThen(f.newIs(&service, &poor), f.newIs(&tips, &cheap)),
					f.newThen(f.newIs(&service, &good),
							f.newIs(&tips, &average))),
			f.newThen(f.newIs(&service, &excellent),
					f.newIs(&tips, &generous)));

	//defuzzification
	Expression<float> *system = f.newMamdani(r, &tips);

	//apply input
	float s;
	while (true) {
		printf("Ingrese Temperatura Medida:");
		scanf("%f", &s);
		service.setValue(s);
		printf("Resultado para setear al pwm del MOSFET=%f\n",
				128 - system->evaluate() * 128);

	}
}

void Fuzzy::testSugeno() {
	//utils
	Interval<float> interval = Interval<float>(5, 25, 1);

	//operators
	NotMinus1<float> opNot;
	AndMin<float> opAnd;
	OrMax<float> opOr;
	SugenoThen<float> opThen;
	AggMax<float> opAgg;
	CogDefuzz<float> opMamdani = CogDefuzz<float>(&interval);
	SugenoDefuzz<float> opSugeno = SugenoDefuzz<float>();

	vector<float> coef;
	coef.push_back(1);
	coef.push_back(1);
	SugenoConclusion<float> opConclusion = SugenoConclusion<float>(&coef);

	//fuzzy expession factory
	FuzzyFactory<float> f(&opNot, &opAnd, &opOr, &opThen, &opAgg, &opMamdani,
			&opSugeno, &opConclusion);

	//membership function
	IsTriangle<float> poor(-5, 0, 5);
	IsTriangle<float> good(0, 5, 10);
	IsTriangle<float> excellent(5, 10, 15);
	IsTriangle<float> rancid(-5, 0, 5);
	IsTriangle<float> delicious(5, 10, 15);

	//values
	ValueModel<float> service(0);
	ValueModel<float> food(0);

	//Sugeno conclu
	vector<const Expression<float>*> SCservicefood;
	SCservicefood.push_back(&service);
	SCservicefood.push_back(&food);

	vector<const Expression<float>*> SCservice;
	SCservice.push_back(&service);

	//Regles
	vector<const Expression<float>*> regles;

	regles.push_back(
			f.newThen(
					f.newOr(f.newIs(&service, &poor), f.newIs(&food, &rancid)),
					f.newConclusion(&SCservicefood)));

	regles.push_back(
			f.newThen(f.newIs(&service, &good), f.newConclusion(&SCservice)));

	regles.push_back(
			f.newThen(
					f.newOr(f.newIs(&service, &excellent),
							f.newIs(&food, &delicious)),
					f.newConclusion(&SCservicefood)));

	//defuzzification
	Expression<float> *system = f.newSugeno(&regles);

	//apply input
	float s;
	while (true) {

		printf("service:");
		scanf("%f", &s);
		service.setValue(s);
		printf("food:");
		scanf("%f", &s);
		service.setValue(s);
		printf("tips ->  %f", system->evaluate());
	}
}

Fuzzy::Fuzzy() {
	// TODO Auto-generated constructor stub

}

Fuzzy::~Fuzzy() {
	// TODO Auto-generated destructor stub
}

