(* ::Package:: *)

BeginPackage["SolveInFiniteFields`",{"FiniteFields`"}]


solveGF::usage = "solveGF[p,n,variables,ideal] finds the solutions of the equations given by the ideal (without '== 0') in GF(p^n)."


Begin["Private`"]


solveGF[p_,n_,variablesInput_,ideal_,outputpoly_:True,debug_:False]:=
	Module[{q,variables,elementsGF,gbasis,gbasisold,simplegbasis,
		simplesols,variablesInEquation,varaux,idealaux,solaux,
		varssimplesols,tuples,relation,assignations,postuples,sol},

		variables=variablesInput;
		q=p^n;
		elementsGF=Join[{0},NestList[Successor,GF[q][{1}],q-2]];
		gbasis=GroebnerBasis[ideal,variables,Modulus->p];

		simplesols={};
		If[Length[variables]>1,	
			variablesInEquation[eq_,vr_]:=Select[Variables[eq],Function[u,MemberQ[vr,u]]];
			Do[
				varaux=variables[[i]];
				idealaux=Select[ideal,Function[u,Length[variablesInEquation[u,variables]]==1
					&& variablesInEquation[u,variables]=={varaux}]];
				solaux=solveGF[p,n,Cases[Variables[idealaux],varaux],idealaux,outputpoly];
				If[solaux!={{}} && Length[solaux]==1,
					AppendTo[simplesols,solaux//Flatten]],
				{i,1,Length[variables]}
			];
			simplesols=simplesols//Flatten;
			varssimplesols=#[[1]]& /@ simplesols;
			variables=Select[variables,FreeQ[varssimplesols,#]&];
			gbasisold=gbasis;
			
			gbasis=gbasis/.simplesols;
			gbasis=GroebnerBasis[gbasis,variables,Modulus->p];
			If[debug,Print["Simple solutions ",simplesols,"\nVars solved ",varssimplesols,"\nAll vars ",variablesInput,
				"\nVars to solve ",variables,"\nIdeal before ",gbasisold,"\nIdeal after ",gbasis]];
		];

		tuples=Tuples[elementsGF,Length[variables]];
		relation=Table[Table[variables[[i]]->tuple[[i]],{i,Length[variables]}],{tuple,tuples}];
		assignations=Table[gbasis/.rel,{rel,relation}];
		postuples=Position[assignations,ConstantArray[0,Length[gbasis]]]//Flatten;
		sol=Table[tuples[[pos]],{pos,postuples}];
		If[outputpoly,
			sol=Table[Table[If[ToElementCode[el]==0,0,ElementToPolynomial[el,\[FormalX]]],{el,element}],{element,sol}]
		];
		sol=Table[Table[variables[[i]]->s[[i]],{i,1,Length[variables]}],{s,sol}];
		sol=Table[Join[s,simplesols],{s,sol}];
		If[debug,Print["Solutions ",sol,"\nSolutions(tuple index) ",postuples,"\nAssignations ",assignations,
			"\nRelations ",relation,"\nGroebnerBasis ",gbasis,"\nTuples ",tuples,"\nElements of GF ",elementsGF,
			"\nIdeal ",ideal,"\nVariables ",variables]];
		sol
	]


solveGFold[p_,n_,variables_,ideal_,outputpoly_:True,debug_:False]:=
	Module[{q,elementsGF,tuples,gbasis,relation,assignations,postuples,sol},
		q=p^n;
		elementsGF=Join[{0},NestList[Successor,GF[q][{1}],q-2]];
		tuples=Tuples[elementsGF,Length[variables]];
		gbasis=GroebnerBasis[ideal,variables,Modulus->p];
		relation=Table[Table[variables[[i]]->tuple[[i]],{i,Length[variables]}],{tuple,tuples}];
		assignations=Table[gbasis/.rel,{rel,relation}];
		postuples=Position[assignations,ConstantArray[0,Length[gbasis]]]//Flatten;
		sol=Table[tuples[[pos]],{pos,postuples}];
		If[outputpoly,
			sol=Table[Table[If[ToElementCode[el]==0,0,ElementToPolynomial[el,\[FormalX]]],{el,element}],{element,sol}]
		];
		sol=Table[Table[variables[[i]]->s[[i]],{i,1,Length[variables]}],{s,sol}];
		If[debug,Print["Solutions ",sol,"\nSolutions(tuple index) ",postuples,"\nAssignations ",assignations,
			"\nRelations ",relation,"\nGroebnerBasis ",gbasis,"\nTuples ",tuples,"\nElements of GF ",elementsGF,
			"\nIdeal ",ideal,"\nVariables ",variables]];
		sol
	]


(* solveGF[p_,n_,variables_,ideal_]:=
	Module[{q,gf,elementsGF,tuples,gbasis,f,irrpoly,sol},
		q=p^n;
		SetFieldFormat[GF[q],FormatType->FunctionOfCode[gf]];
		elementsGF=Union[{0},Table[ElementToPolynomial[gf[i],\[FormalX]],{i,1,q-1}]];
		tuples=Tuples[elementsGF,Length[variables]];
		gbasis=GroebnerBasis[ideal,variables,Modulus->p];
		f[s_]:=Function[u,gbasis/.Table[u[[i]]->s[[i]],{i,Length[variables]}]][variables];
		irrpoly=FieldIrreducible[GF[q],\[FormalX]];
		Print[gbasis];
		sol=Cases[tuples,
			q_ /; Table[PolynomialRemainder[f[q][[i]],irrpoly,\[FormalX],Modulus->p],{i,Length[gbasis]}]
				== Table[0,{i,Length[gbasis]}]
		];
		sol
	]
*)


End[]


EndPackage[]
