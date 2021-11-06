#include <iostream>
#include <string.h>
#include <conio.h>
#define RUTAUSUARIO "usuarios.bin"
#define RUTACOMPRA "procesados.bin"
using namespace std;

struct usuario
{
        char id[6];
        int fecha;
        bool activo = false;
        float importeu = 0;
        char mail[50];

};
struct compra
{
        int idcompra;
        long long fechahora;
        float importec = 0;
        char idusuario[6];
        int articulo;

};

void mostrarMenu()
{
    cout << "Elija una opcion:\n";
    cout << "1 - Levantar Usuarios." << endl;
    cout << "2 - Agregar Nuevo Usuario." << endl;
    cout << "3 - Buscar un Usuario." << endl;
    cout << "4 - Desactivar un Usuario Existente." << endl;
    cout << "5 - Listar Usuarios Activos por Orden de Importe." << endl;
    cout << "6 - Procesar un lote de compras." << endl;
    cout << "7 - Mostrar compras por ID del cliente." << endl;
    cout << "8 - Reporte de compras en formato HTML. " << endl;
    cout << "9 - Reporte de compras en formato CSV." << endl;
    cout << "0 - Finalizar jornada." << endl;
    return;
}
void menuBuscar()
{
    cout << "Elija una opcion: " << endl;
    cout << "1 - Buscar usuario por ID. " << endl;
    cout << "2 - Buscar usuario por Email. " << endl;
    cout << "3 - Volver al Menu principal." << endl;
    return;
}
void leerUsuario(usuario &a)
{
        cout << "Ingrese id: " << endl;
        cin >> a.id;
        cout << "Ingrese la fecha de alta: " << endl;
        cin >> a.fecha;
        cout << "Ingrese email:" << endl;
        cin >> a.mail;
        a.activo=true;
        return;

}

bool agregarUsuario(char rutanombre[])
{
    FILE *f;
    usuario a;
    if (f = fopen(rutanombre, "ab"))
    {
        leerUsuario(a);
        fwrite(&a, sizeof(usuario), 1, f);
        fclose(f);
        return true;
    }
    return false;
}
void mostrarUsuario(usuario a)
{
    cout << "********* " << a.id << " *********" << endl;
    cout << "Fecha de Creacion: " << a.fecha << endl;
    cout << "Importe Total: " << a.importeu<< endl;
    cout << "E-Mail: " << a.mail<< endl;
    cout << endl;
}
void mostrarTodo(char rutanombre[])
{
    FILE *f;
    usuario a;
    if (f = fopen(rutanombre, "rb"))
    {
        while (fread(&a, sizeof(usuario),1, f))
        {
            if (a.activo)
                mostrarUsuario(a);
        }
        fclose(f);
    }
    else
        cout << "No se pudo abrir el archivo." << endl;
}
void mostrarcompras(compra a)
{
    cout << "********* " << a.idcompra << " *********" << endl;
    cout << "Fecha y Hora de Compra (AAAAMMDDHHMM) : " << a.fechahora << endl;
    cout << "Importe: " << a.importec<< endl;
    cout << "ID Usuario: " << a.idusuario<< endl;
    cout << "ID Articulo: " << a.articulo<< endl;
    cout << endl;
}
void mostrarTodoC(char rutanombre[])
{
    FILE *f;
    compra a;
    if (f = fopen(rutanombre, "rb"))
    {
        while (fread(&a, sizeof(compra),1, f))
            mostrarcompras(a);
        fclose(f);
    }
    else
        cout << "No se pudo abrir el archivo." << endl;
}
void desactivarUsuario(usuario &a, char idBuscado[6], char rutanombre[])
{
    FILE *f;
    bool encontrado = false;
    if (f=fopen(rutanombre,"rb+"))
    {
        while(!encontrado && fread(&a,sizeof(usuario),1,f))
        {
            if (strcmp(a.id, idBuscado)==0)
            {
                encontrado = true;
                a.activo = false;
                fseek(f,(-1)*sizeof(usuario), SEEK_CUR);
                fwrite(&a,sizeof(usuario),1,f);
            }
        }
        if (!encontrado)
            cout << "No se encontro la persona." << endl;
        fclose(f);
    }
}
void leerCompra(compra &a, char id[],float imp,int idc)
{

    a.idcompra=idc;
    cout << "Compra Nro: "<< a.idcompra << endl;
    cout << "Ingrese la fecha de (AAAAMMDDHHMM) " << endl;
    cin >> a.fechahora;
    strcpy(a.idusuario,id);
    a.importec=imp;
    cout << "Ingrese id del articulo:" << endl;
    cin >> a.articulo;
    return;
}
bool agregarCompra(char rutanombre[],char id[],float imp,int idc)
{
    FILE *f;
    compra a;
    usuario b;
    if (f = fopen(rutanombre, "ab"))
    {
        leerCompra(a,id,imp,idc);
        fwrite(&a, sizeof(compra), 1, f);
        fclose(f);
        return true;
    }
    return false;
}
bool actualizarImporte(usuario a, char id[], char rutanombre[], float imp)
{
    FILE *f;
    usuario b;
    float importeviejo;
    bool encontrado = false;
    int fecha=0;
    char mail[50];
    if (f = fopen(rutanombre, "rb+"))
    {
        while (!encontrado && fread(&b, sizeof(usuario),1, f))
        {
            if (strcmp(b.id,id) == 0)
                encontrado = true;
                fecha=b.fecha;
                strcpy(mail,b.mail);
                importeviejo=b.importeu;
        }
        if (encontrado)
        {
            fseek(f, (-1)*sizeof(usuario), SEEK_CUR);
            a.activo=true;
            a.fecha=fecha;
            strcpy(a.id,id);
            strcpy(a.mail,mail);
            a.importeu=importeviejo+imp;
            fwrite(&a, sizeof(usuario),1 , f);
        }
        fclose(f);
    }
    return encontrado;

}
void compraXusuario(compra &a, char idBuscado[6], char rutanombre[])
{
    FILE *f;
    if (f = fopen(rutanombre, "rb"))
    {
        while (fread(&a, sizeof(compra),1, f))
        {
            if (strcmp(a.idusuario,idBuscado) == 0)
              {
                mostrarcompras(a);
              }
        }
        fclose(f);
    }
    return;
}
bool buscarusuarioXMail(usuario &a, char mailBuscado[50], char rutanombre[])
{
    FILE *f;
    bool encontrado = false;
    if (f = fopen(rutanombre, "rb"))
    {
        while (!encontrado && fread(&a, sizeof(usuario),1, f))
        {
            if (strcmp(a.mail,mailBuscado) == 0)
                encontrado = true;
        }
        fclose(f);
    }
    return encontrado;
}
bool buscarusuarioXId(usuario &a, char idBuscado[6], char rutanombre[])
{
    FILE *f;
    bool encontrado = false;
    if (f = fopen(rutanombre, "rb"))
    {
        while (!encontrado && fread(&a, sizeof(usuario),1, f))
        {
            if (strcmp(a.id,idBuscado) == 0)
                encontrado = true;
        }
        fclose(f);
    }
    return encontrado;
}
void ordenarXimporte(usuario v[], int tamlogico)
{
    usuario aux;
    int j = 0;
    for (int i = 0; i <  tamlogico - 1; i++)
    {
       for(j =0; j < tamlogico - 1 - i; j++)
       {

           if (v[j+1].importeu> v[j].importeu)
           {
               aux = v[j];
               v[j] = v[j+1];
               v[j+1] = aux;
           }
       }
    }
    return;
}
void ordenarXid(usuario v[], int tamlogico)
{
    usuario aux;
    int j = 0;
    for (int i = 0; i <  tamlogico - 1; i++)
    {
       for(j =0; j < tamlogico - 1 - i; j++)
       {
           if (strcmp(v[j+1].id, v[j].id) < 0)
           {
               aux = v[j];
               v[j] = v[j+1];
               v[j+1] = aux;
           }
       }
    }
    return;
}
void escribirHTML(char rutanombre[])
    {
    long long fechamax,fechamin;
    compra compaux;
    float acum; bool Flag=true;
    FILE *f, *E;
    f = fopen("salidahtml.html", "wt"); E = fopen(rutanombre, "rb");

    system("CLS");

        cout<<"\n\n\t\t Ingrese la fecha maxima a buscar: ";
        cin>>fechamax;
        cout<<"\n\t\t Ingrese la fecha minima a buscar: ";
        cin>>fechamin;
        fprintf(f,"<html><body>\n");
        fprintf(f,"<h1><p style='color:#2F075F';>Reporte de compras efectuadas\n</p></h1>");
        fprintf(f,"<table border=1>\n");
        fprintf(f,"<th>CompraID</th><th>FechaHora</th><th>Monto</th><th>UsuarioID</th><th>Nroarticulo</th><th>Importe Total</th>\n");

        fread(&compaux, sizeof(compra), 1, E);
        while (!feof(E))
        {
            if(compaux.fechahora>fechamin && compaux.fechahora<fechamax)
            {
            	acum+=compaux.importec;
	            fprintf(f,"<tr>\n");
    	        fprintf(f,"<td><p style='color:#2F075F';>%d</p></td><td><p style='color:#2F075F';>%lld</p></td><td><p \
				style='color:#2F075F';>%f</p></td><td><p style='color:#2F075F';>%s</p></td><td><p style='color:#2F075F';>%d</p></td>\n",compaux.idcompra,compaux.fechahora,compaux.importec,compaux.idusuario,compaux.articulo);
        	    fprintf(f,"</tr>\n");
            }
    		fread(&compaux, sizeof(compra), 1, E);
        }
        fprintf(f,"<tr>\n");
        fprintf(f,"<td> </td><td> </td><td> </td><td> </td><td> </td><td><p style='color:#2F075F';>%f</p></td>\n",acum);
        fprintf(f,"</tr>\n");
        fprintf(f, "</table>");
        fprintf(f, "</body>");
        fprintf(f, "</html>");
        fclose(f); fclose(E);
        return;
}
void escribirCSV(char rutanombre[]){
    long long fechamax,fechamin;
    compra compaux;
    float acum;
    FILE *f, *E;
    f = fopen("salidaexcel.csv", "wt"); E = fopen(rutanombre, "rb");

        	cout<<"\n\n\t\t Ingrese la fecha maxima a buscar: ";
        	cin>>fechamax;
        	cout<<"\n\t\t Ingrese la fecha minima a buscar: ";
	        cin>>fechamin;
    fprintf(f,"CompraID;FechaHora;Monto;UsuarioID;Nroarticulo;Importe total\n");
	fread(&compaux, sizeof(compra), 1, E);
    while(!feof(E)){
               if(compaux.fechahora>fechamin && compaux.fechahora<fechamax)
                {
                    acum+=compaux.importec;
                	fprintf(f,"%d;%lld;%f;%s;%d\n",compaux.idcompra,compaux.fechahora,compaux.importec,compaux.idusuario,compaux.articulo);
               }
               fread(&compaux, sizeof(compra), 1, E);
    }
    fprintf(f,"%c;%c;%c;%c;%c;%.2f\n",' ',' ',' ',' ',' ',acum);
    fclose(f);
    return;
}

int main()
{
    FILE *f;
    usuario a;
    compra z;
    char id[6];
    char mail [50];
    int opcion=0;
    int opcionb=0;
    float importe=0;
    int contcompra=0;
    do
    {
        cout << "Trabajo Practico 2:" << endl;
        mostrarMenu();
        do
            cin>>opcion;
        while(opcion>='1' && opcion<='10');
        switch (opcion)
        {
            case 1:
                    {
                        usuario vusr[2048];
                        int cant_usr;
                        if (f = fopen(RUTAUSUARIO, "rb"))
                        {
                            fseek(f, 0, SEEK_END);
                            cant_usr = ftell(f)/ sizeof(usuario);
                            fseek(f, 0, SEEK_SET);
                            fread(vusr, sizeof(usuario),cant_usr, f);
                            ordenarXid(vusr, cant_usr);
                            fclose(f);
                        }
                        if (f = fopen(RUTAUSUARIO, "wb"))
                        {
                            fwrite(vusr,sizeof(usuario), cant_usr, f);
                            fclose(f);
                        }
                        mostrarTodo(RUTAUSUARIO);
                    }
            break;
            case 2:
                    agregarUsuario(RUTAUSUARIO);
                break;
            case 3:
                do
                {
                    cout << "Buscar Usuario:" << endl;
                    menuBuscar();
                    do
                        cin>> opcionb;

                    while (opcionb <=1 && opcionb>=3);

                    if(opcionb == 1)
                    {
                            cout << "Ingrese  el id a buscar: " << endl;
                            cin >>  id;
                            if (buscarusuarioXId(a,id,RUTAUSUARIO))
                            {
                                mostrarUsuario(a);
                            }

                            else
                                cout << "El usuario no está en el archivo." << endl;
                    }
                    else
                        if (opcionb == 2)
                        {
                                cout << "Ingrese  el Mail a buscar: " << endl;
                                cin >>  mail;
                                if (buscarusuarioXMail(a,mail,RUTAUSUARIO))
                                    mostrarUsuario(a);
                                else
                                cout << "El usuario no está en el archivo." << endl;
                        }
                }
                while (opcionb != 3);
                break;
                case 4:
                    cout << "Desactivar usuario:" << endl;
                    cout << "Ingrese  el id del usuario a desactivar: " << endl;
                    cin >>  id;
                    desactivarUsuario(a,id,RUTAUSUARIO);;
                break;
                case 5:
                    {
                        usuario vusr[2048];
                        int cant_usr;
                        if (f = fopen(RUTAUSUARIO, "rb"))
                        {
                            fseek(f, 0, SEEK_END);
                            cant_usr = ftell(f)/ sizeof(usuario);
                            fseek(f, 0, SEEK_SET);
                            fread(vusr, sizeof(usuario),cant_usr, f);
                            ordenarXimporte(vusr, cant_usr);
                            fclose(f);
                        }
                        if (f = fopen(RUTAUSUARIO, "wb"))
                        {
                            fwrite(vusr,sizeof(usuario), cant_usr, f);
                            fclose(f);
                        }
                        mostrarTodo(RUTAUSUARIO);
                    }
                break;
                case 6:
                    cout << "Procesar un lote de compras: " << endl;
                    cout << "Ingrese  el id del usuario: " << endl;
                    cin >>  id;
                    cout << "Ingrese el monto de la compra:" << endl;
                    cin >> importe;
                    contcompra++;
                    agregarCompra(RUTACOMPRA,id,importe,contcompra);
                    /*Actualiza el importe del usuario*/
                    actualizarImporte(a,id,RUTAUSUARIO,importe);
                break;
                case 7:
                    cout << "Mostrar compras por usuario: "<< endl;
                    cout << "Ingrese ID del usuario: "<< endl;
                    cin>>id;
                    compraXusuario(z,id,RUTACOMPRA);
                break;
                case 8:
                        cout << "Escribir Reprote HTML: "<< endl;
                        escribirHTML(RUTACOMPRA);
                break;
                case 9:
                        cout << "Escribir Reprote CSV: "<< endl;
                        escribirCSV(RUTACOMPRA);
                break;
                case 0:
                return 0;
                break;


        }

    }
    while (opcion != 27);
    return 0;
}
