(* ::Package:: *)

BeginPackage["GraphColoring`"]


colorGraph::usage = "colorGraph[graph,numbercolors] finds all the vertex colorations which satisfies the condition no two adjacent vertices share the same color."


Begin[ "Private`"]


colorGraph[graph_,numbercolors_] :=
	Module[ {n,d,EL,pol,t1,t2,ideal,indeterminates,grobBasis,sol},
		d = numbercolors;
		n = Length[VertexList[graph]];
		EL = EdgeList[graph];
		Switch[d,3,{pol[i_,j_]:=\!\(\*SubsuperscriptBox[\(x\), \(i\), \(2\)] + \(\*SubscriptBox[\(x\), \(i\)]\ 
				\*SubscriptBox[\(x\), \(j\)]\) + \*SubsuperscriptBox[\(x\), \(j\), \(2\)] - 1\);t1=Table[Subscript[x, i]^d-Subscript[x, i],{i,1,n}]},
			4,{pol[i_,j_]:=\!\(\*SubsuperscriptBox[\(x\), \(i\), \(3\)] + \(\*SubsuperscriptBox[\(x\), \(i\), \(2\)]\ 
				\*SubscriptBox[\(x\), \(j\)]\) + \(\*SubscriptBox[\(x\), \(i\)]\ \*SubsuperscriptBox[\(x\), \(j\), \(2\)]\) + 
				\*SubsuperscriptBox[\(x\), \(j\), \(3\)]\);t1=Table[Subscript[x, i]^d-1,{i,1,n}]}];
		t2=Table[pol[EL[[i]][[1]],EL[[i]][[2]]],{i,1,Length[EL]}];
		ideal = Union[t1,t2];
		indeterminates=Table[Subscript[x, i],{i,1,n}];
		Switch[d,3,grobBasis=GroebnerBasis[ideal,indeterminates,Modulus->3],
			4,grobBasis=GroebnerBasis[ideal,indeterminates]];
		Switch[d,3,sol=Solve[Table[grobBasis[[i]]==0,{i,1,Length[grobBasis]}],indeterminates,Modulus->3],
			4,sol=Solve[Table[grobBasis[[i]]==0,{i,1,Length[grobBasis]}],indeterminates]];
		Switch[d,3,Manipulate[GraphPlot[graph,VertexRenderingFunction->({Switch[sol[[i]][[#2]][[2]],0,Red,1,Green,2,Yellow],
				EdgeForm[Black],Disk[#,.1],Black,Text[#2,#1]}&)],{i,1,Length[sol],1}],
			4,Manipulate[GraphPlot[graph,VertexRenderingFunction->({Switch[sol[[i]][[#2]][[2]],1,Red,-1,Green,I,Yellow,-I,Brown],
				EdgeForm[Black],Disk[#,.1],Black,Text[#2,#1]}&)],{i,1,Length[sol],1}]]
	]


End[]


EndPackage[]
