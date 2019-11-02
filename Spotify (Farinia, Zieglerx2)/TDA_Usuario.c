#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "TDA_Usuario.h"


const char ESC = 27;

int ingresarusuario(char nombarchi)             ///retorna cero si ingreso correctamente
{
   FILE* fichero ;
   stUsuario user;
   int control_user=0;
   int control_pass=0;
   int verificacion=0;
   fichero=fopen(nombarchi,"rb");
   if(fichero==NULL)
   {
      fichero=fopen(nombarchi,"rb");
   }
   if(fichero!=NULL)
   {
       while(fread(&user, sizeof(stUsuario), 1, fichero)>0)
       {
          system("cls");
          ///ingresar aqui un mensaje de beinvenida (Spotify trial)
          gotoxy(10,12);
          printf("Ingrese un nombre de usuario: ");
          gets(user.nombreUsuario);
          control_user=ver_exist_user(nombarchi, user.nombreUsuario);
          while(control_user!=1)
          {
              gotoxy(10,12);
              printf("                                                          ");
              gotoxy(10,12);
              SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),140);
              printf("Ingrese un usuario valido por favor: ");
              SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),143);
              gets(user.nombreUsuario);
              control_user=ver_exist_user(nombarchi, user.nombreUsuario);
          }
          gotoxy(10,16);
          printf("Ingrese su contrase%ca : ",164);
          gets(user.pass);
          control_pass = ver_exist_pass(nombarchi, user.pass);
          while(control_pass!=1)
          {
              gotoxy(10,12);
              printf("                                                          ");
              gotoxy(10,12);
              SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),140);
              printf("Ingrese una contrase%ca valida por favor: ", 165);
              SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),143);
              gets(user.pass);
              control_pass=ver_exist_user(nombarchi, user.pass);
          }
        }
    }
    fclose(fichero);
    return verificacion;
}


stUsuario cargarUnUsuario()
{
    int admin;
    stUsuario a;
    a.idUsuario = buscaUltimoID() + 1; /// BUSCAMOS ULTIMO ID EN ARCHIVO, Y LE SUMAMOS 1.
    printf("Ingrese el nombre de Usuario: \n");
    fflush(stdin);
    gets(&a.nombreUsuario);

    printf("Ingrese la contrase�a: \n");
    fflush(stdin);
    gets(&a.pass);

    printf("A�o de nacimiento: \n");
    scanf("%d", &a.anioNacimiento);

    printf("Ingrese el sexo: \n");
    fflush(stdin);
    gets(&a.sexo);

    printf("Ingrese el pais de origen: \n");
    fflush(stdin);
    gets(&a.pais);

    fflush(stdin);
    admin = versieslaprimeravez(arUsuario);
    if (admin == 0)
    {
        a.admin = 1;
    }
    else if (admin = 1)
    {
        a.admin = 0;
    }
    a.eliminado = 0;

    guardarUsuario(a);
}

int versieslaprimeravez(char nombarchius)        ///si retorna 0 no hay admin, si retorna 1 existe admin
{
   int flag = 0;
   FILE * ficherous;
   stUsuario user;
   ficherous = fopen(arUsuario,"rb");
   if (ficherous == NULL)
   {
       flag = 0;
   }
    while(fread(&user,sizeof(stUsuario),1,ficherous)>0 && flag == 0)
        {
            if(user.admin == 1)
            {
                flag = 1;
            }

        }
    fclose(ficherous);
   return flag;
}

void guardarUsuario(stUsuario a)
{
    FILE * parchi = fopen(arUsuario, "ab");
    if(parchi != NULL)
        {
            fwrite(&a, sizeof(stUsuario), 1, parchi);
        }
        fclose(parchi);
}
void muestraUnUsuario(stUsuario a)
{
    printf("ID: %d \n", a.idUsuario);
    printf("Nombre del Usuario: %s \n", a.nombreUsuario);
    printf("A�o de nacimiento: %d \n", a.anioNacimiento);
    printf("Sexo: %s \n", a.sexo);
    printf("Pais: %s \n", a.pais);
    printf("Nivel de Admin (0=Usuario, 1=Admin) : [%d] \n", a.admin);

    /// NO MOSTRAMOS ELIMINADO, PORQUE LO USAMOS COMO FILTRO
}
void muestraTodosLosUsuarios()
{
    stUsuario a;
    FILE * parchi = fopen(arUsuario, "rb");
    if(parchi != NULL)
    {
        while(fread(&a, sizeof(stUsuario), 1, parchi)>0)
            {
                    muestraUnUsuario(a);
                }
            }
    fclose(parchi);
}
void BajaUsuario(char nombreFiltro) /// USAMOS COMO REFERENCIA EL CAMPO "NOMBRE DE USUARIO" DEL USUARIO
{
    int flag = 0;
    stUsuario a;
    FILE * parchi = fopen(arUsuario, "a+b");
    if(parchi != NULL)
    {
        while(flag == 0 && (fread(&a, sizeof(stUsuario), 1, parchi)>0))
        {
            if(strcmp(a.nombreUsuario, nombreFiltro)==0)
            {
                fseek(parchi, sizeof(stUsuario)*(-1), SEEK_CUR);
                a.eliminado = 1;
                fwrite(&a, sizeof(stUsuario), 1, parchi);
                flag = 1;
            }
        }
    }
    fclose(parchi);
}
stUsuario opcionCampo(stUsuario a) /// FUNCION QUE USAMOS PARA SELECCIONAR LA OPCION QUE QUEREMOS MODIFICAR.
{
    int opsw;
    printf("Ingrese la opcion que desea modificar: \n");
    printf("1- Nombre de Usuario: \n");
    printf("2- Contrase�a: \n");
    printf("3- A�o de nacimiento: \n");
    printf("4- Sexo: \n");
    printf("5- Pais: \n");
    scanf("%d", &opsw);

    switch(opsw){
    case 1:
        {
            printf("Ingrese nombre de usuario a modificar: \n");
            fflush(stdin);
            gets(&a.nombreUsuario);

        }break;
    case 2:
        {
            printf("Ingrese contrase�a nueva: \n");
            fflush(stdin);
            gets(&a.pass);

        }break;
    case 3:
        {
            printf("A�o de nacimiento a reemplazar: \n");
            scanf("%d", &a.anioNacimiento);

        }break;
    case 4:
        {
            printf("Ingrese el sexo a modificar: \n");
            fflush(stdin);
            gets(&a.sexo);

        }break;
    case 5:
        {
            printf("Ingrese el nuevo pais: \n");
            fflush(stdin);
            gets(&a.pais);
            /// COSAS LINDAS A MODIFICAR, HACER UN SWITCH DE PAISES ASI ES MAS COMODO.
        }break;
    }
    return a;
}
void modificacionUsuario(char nombreFiltro)
{
    int flag = 0;
    stUsuario a;
    FILE * parchi = fopen(arUsuario, "r+b");
    if(parchi != NULL)
    {
        while((flag == 0) && (fread(&a, sizeof(stUsuario), 1, parchi)>0))
        {
            if(strcmp(a.nombreUsuario, &nombreFiltro)!=0)
                {
                    fseek(parchi, sizeof(stUsuario)*(-1), SEEK_CUR);
                    a = opcionCampo(a);
                    fwrite(&a, sizeof(stUsuario), 1, parchi);
                    flag = 1;
                }
        }
    }
    fclose(parchi);
}
int buscaUltimoID()
{
   stUsuario a;
   int id = 0;
   FILE * parchi = fopen(arUsuario, "rb");
   if(parchi != NULL)
   {
       while(fread(&a, sizeof(stUsuario), 1, parchi)>0)
       {
           id = a.idUsuario;
       }
   }
       fclose(parchi);
       return id;
}


int ver_exist_user(char nombarchius [], char usaux[])
{
   int flag=0;
   FILE* ficherous;
   stUsuario user;
   ficherous=fopen(nombarchius,"rb");
   if (ficherous == NULL)
   {
      printf ("\n el archivo no existe");
   }
   else
   {
        while(fread(&user,sizeof(stUsuario),1,ficherous)>0 && flag==0)
        {
            if(strcmp(user.nombreUsuario,usaux)==0)
            {
                flag=1;
            }

        }
    fclose(ficherous);
   }
   return flag;
}

int ver_exist_pass(char nombarchius [], char passaux[])
{
   int flag=0;
   FILE* ficherous;
   stUsuario user;
   ficherous=fopen(nombarchius,"rb");
   if (ficherous == NULL)
   {
      printf ("\n el archivo no existe");
   }
   else
   {
        while(fread(&user,sizeof(stUsuario),1,ficherous)>0 && flag==0)
        {
            if(strcmp(user.pass,passaux)==0)
            {
                flag=1;
            }

        }
    fclose(ficherous);
   }
   return flag;
}

