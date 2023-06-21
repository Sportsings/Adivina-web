//Codigo para crear un juego de adivinanzas usando C, html y css
#include <webci.h>
#include <sqlite3.h>
#include <curl/curl.h>

//Variables globales para las respuesta
String respuesta;//variable para la respuesta a comparar
String respuesta2;//variable para la respuesta a mostrar

int random_number(int);//funcion para generar numeros aleatorios y con ellos las adivinanzas
String adivina ();//funcion para generar las adivinanzas
void send_main_code (String, struct Server);

int main (){
    struct Server adivinas; //estructura para poder crear el servidor
    String adivinanza;//variable que tendra las adivinanzas
    int respuestas;//variable para poder romper el bucle de las repuestas con los mensajes de 'incorrecto' y 'correcto''
    adivinas.buffer_size = 4024;
    adivinas.port = 8090;//puerto 8090 porque en mi sistema el 8080 esta muy ocupado
    start_server_file(&adivinas);
    while(WEB_TRUE){//bucle principal de donde se envian las respuesta
        adivinanza = adivina();
        send_main_code(adivinanza,adivinas);//funcion que envia como respuesta un codigo html principal
        printf("%s\n",get_response());//imprimimos las solicitudes o respuestas enviadas por el navegador
        if(get_POST(get_response(),"result=",7,11) != WEB_ERROR){//condicion para ver si se ha enviado una respuesta
            _post = get_POST(get_response(),"result=",7,11);
            respuestas = WEB_TRUE;//Se le asigna el valor WEB_TRUE para crear bucles inderteminados
            if(strcmp(respuesta,_post) == 0){//se compara la respuesta generada con la respuesta del usuario
                while(respuestas){
                    send_response_inst(&adivinas,"<meta charset=\"UTF-8\"><center><h1>¡Correcto!</h1></center><center><button><a href=\"index.html\">Volver</a></button></center><script>alert('¡Correcto!');</script>");
                    if(search_words(get_response(),"index.html") == WEB_OK){
                        respuestas = WEB_FALSE;
                    }
                }
            } else {
                while(respuestas){
                    send_response_varic(&adivinas,1,"<meta charset=\"UTF-8\"><center><h1>¡Incorrecto la respuesta es: %s</h1></center><center><p><button><a href=\"index.html\">Volver</a></button></p></center><script>alert('¡Incorrecto!');</script>",respuesta2);
                    if(search_words(get_response(),"index.html") == WEB_OK){
                        respuestas = WEB_FALSE;
                    }
                }
            }
        }
    }
    return 0;
}

void send_main_code (const String adivinanza, struct Server s){
    send_response_varic(&s,1,"<meta charset=\"UTF-8\"><style>.container {max-width: 400px;margin: 0 auto;text-align: center;}.question {font-size: 20px;}input[type=\"text\"] {padding: 10px;margin-bottom: 10px;}button {padding: 10px 20px;background-color: #4CAF50;color: white;border: none;cursor: pointer;}button:hover {background-color: #45a049;}</style><title>Adivina web</title><center><h1>Adivina web</h1></center><div class=\"container\"><p class=\"question\">%s</p><form method=\"\"><input type=\"text\" name=\"result\" id=\"result\"><input type=\"submit\" value=\"Vereficar\"></form></div><script>alert('Bienvenido a la pagina de Adivina web');</script>",adivinanza);
}

int random_number (int max){
    int inicio;
	srand(time(NULL));
	inicio = rand() % max;
	return inicio;
}

String adivina (){
    
    int result;
    result = random_number(10);
    String adivinanza;
    
    if(result == 1){
        adivinanza = "Suena a la misma hora todas las mañanas, para decirnos a todos: ¡Fuera de la cama!";
        respuesta = "El+despertador";
        respuesta2 = "El despertador";
    } else if(result == 2){
        adivinanza = "Me pones y me quitas, me tomas y me dejas, conmigo no tiritas y estoy hecho de madejas.";
        respuesta = "El+jersey";
        respuesta2 = "El jersey";
    } if(result == 3){
        adivinanza = "Soy bonito por delante algo feo por detrás; me transformo a cada instante, ya que imito a los demás.";
        respuesta = "El+espejo";
        respuesta2 = "El espejo";
    } else if(result == 4){
        adivinanza = "Ruedo, ruedo y en los bolsillos me quedo";
        respuesta = "La+moneda";
        respuesta2 = "La moneda";
    } if(result == 5){
        adivinanza = "Viene y va y lo que antes estaba... ¡ya no está!";
        respuesta = "La+goma+de+borrar";
        respuesta2 = "La goma de borrar";
    } else if(result == 6){
        adivinanza = "Tiene luna, no es planeta; tiene marco y no es puerta.";
        respuesta = "El+espejo";
        respuesta2 = "El espejo";
    } if(result == 7){
        adivinanza = "Tengo copa y no soy árbol, tengo alas y no soy pájaro; protejo del sol a mi amo en invierno y en verano.";
        respuesta = "El+sombrero";
        respuesta2 = "El sombrero";
    } else if(result == 8){
        adivinanza = "Pequeña como una pera, alumbra la casa entera.";
        respuesta = "La+bombilla";
        respuesta2 = "La bombilla";
    } if(result == 9){
        adivinanza = "Mi ser por un punto empieza, por un punto ha de acabar, el que mi nombre acierte sólo dirá la mitad.";
        respuesta = " La+media";
        respuesta2 = " La media";
    } else if(result == 10){
        adivinanza = "Lana sube, lana baja ¿Qué es?";
        respuesta = "La+navaja";
        respuesta2 = "La navaja";
    } if(result == 0){
        adivina();
    }
    return adivinanza;
}
