#version 330 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D ambient;
	sampler2D normal;
	float shininess;
	float shininess_strength;
};

struct Luces
{
	int activa;
	int esLocal;
	int esFocal;
	vec3 cAmbiente;
	vec3 colorDS;
	vec3 posicion;
	vec3 vectorMedio;
	vec3 direcCono;
	float spotCosCutOff;
	float spotExponent;
	float atenuacionConstante;
	float atenuacionLinial;
	float atenuacionCuadratica;
};

const int LuMax = 30;
uniform Luces luz[LuMax];
uniform float Shininess;
uniform float Strength;
uniform Material material;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

void main()
{
	vec3 scatteredLight = vec3( 0.0 );
	vec3 reflectedLight = vec3( 0.0 );

	for ( int l = 0; l < LuMax; ++l )
	{
		if ( luz[l].activa == 0 )
		{
				continue;
		}

		vec3 halfVector;
		vec3 direccionLuz = luz[l].posicion;
		float atenuacion = 1.0;

		if ( luz[l].esLocal == 1 )
		{
			direccionLuz = direccionLuz - FragPos;
			float distanciaLuz = length(direccionLuz);
			direccionLuz = direccionLuz / distanciaLuz;
			atenuacion = 1.0 / ( luz[l].atenuacionConstante + luz[l].atenuacionLinial * distanciaLuz + luz[l].atenuacionCuadratica * distanciaLuz * distanciaLuz );

			if ( luz[l].esFocal == 1 )
			{
				float spotCos = dot( direccionLuz, -luz[l].direcCono );

				if ( spotCos < luz[l].spotCosCutOff)
				{
					atenuacion = 0.0;
				}
				else
				{
					atenuacion *= pow( spotCos, luz[l].spotExponent );
				}

				//halfVector = normalize( direccionLuz + EyeDirection );
				halfVector = normalize( direccionLuz + vec3( 0, 0, 1 ) );
			}
			else
			{
				halfVector = luz[l].vectorMedio;
			}
		}

		float difusa = max( 0.0, dot( Normal, direccionLuz ) );
		float especular = max( 0.0, dot( Normal, halfVector ) );

		if( difusa == 0.0 )
		{
			especular = 0.0;
		}
		else
		{
			especular = pow( especular, Shininess ) * Strength;
		}

		scatteredLight += ( texture( material.ambient , TexCoords ).rgb * luz[l].cAmbiente * atenuacion ) + ( texture( material.diffuse, TexCoords ).rgb * luz[l].colorDS * difusa ) * atenuacion;
		reflectedLight += ( texture( material.specular , TexCoords ).rgb * luz[l].colorDS ) * especular * atenuacion;
	}

	vec3 rgb = min(scatteredLight + reflectedLight, vec3( 1.0 ) );

	FragColor = vec4(rgb, 1.0);
}
