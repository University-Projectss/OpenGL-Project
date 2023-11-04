#version 330 core

//	Variabile de intrare (dinspre Shader.vert);
in vec4 ex_Color;

//	Variabile de iesire	(spre programul principal);
out vec4 out_Color;		//	Culoarea actualizata;

//	Variabilele uniforme;
uniform int codCol;

//	Actualizeaza culoarea in functie de codCol;
void main(void)
{
  switch (codCol)
  {
	case 0: 
	  out_Color = ex_Color;
	  break;
	case 1: 
		out_Color=vec4 (0.0, 0.0, 1.0, 0.0);
		break;
	// rosu
	case 2:
		out_Color=vec4 (1.0, 0.0, 0.0, 0.0);
		break;
	// gri
	case 3:
		out_Color=vec4(0.2f, 0.2f, 0.2f, 1.0f);
		break;
	// verde 
	case 4:
		out_Color=vec4(0.0f, 0.5f, 0.0f, 1.0f);
		break;
	// galben 
	case 6:
		out_Color=vec4(1.0f, 1.0f, 0.0f, 1.0f);
		break;	
	// negru 
	case 5:
		out_Color=vec4(0.0f, 0.0f, 0.0f, 1.0f);
		break;	
	// portocaliu 
	case 7:
		out_Color=vec4(1.0f, 0.5f, 0.0f, 1.0f);
		break;
	// gri deschis 
	case 8:
		out_Color=vec4(0.5f, 0.5f, 0.5f, 1.0f);
		break;
	default:
		break;
  };
}
 