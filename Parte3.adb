
with Ada.Text_IO; use Ada.Text_IO;  --Lo usamos para leer y escribir en consola
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;  --Para manejar enteros
with Ada.Numerics.Float_Random;   --Para manejar decimales

procedure Main is
   --Definimos las constantes
   MaxCola      : constant Integer := 10;
   NumCajas     : constant Integer := 4;
   TotalClientes : Integer;

   -- Para el tiempo aleatorio de las cajas
   package Rand is new Ada.Numerics.Float_Random;
   Gen : Rand.Generator;


   task Cola is
      entry Entrar(ID : Integer);
      entry Salir(ClienteID : out Integer);
   end Cola;

   task body Cola is
      EnCola: array(1 .. MaxCola) of Integer;
      Primero: Integer := 1;
      Ultimo: Integer := 0;
      EnEspera: Integer := 0;
   begin
      loop
      --Hacemos un loop, donde de ser posible agregamos en la cola,si no, tambien de ser posible Pasamos de la cola de espera a una caja
         select
            when EnEspera < MaxCola =>
               accept Entrar(ID : Integer) do
                  Ultimo := (Ultimo mod MaxCola) + 1; --Marcamos ultima pos del array registrada
                  EnCola(Ultimo) := ID; --Guardamos el ultimo
                  EnEspera := EnEspera + 1;
                  Put_Line("Usuario" & Integer'Image(ID) & " entra a la cola de espera.");
               end;
         or
            when EnEspera > 0 =>
               accept Salir(ClienteID : out Integer) do
                  ClienteID := EnCola(Primero);
                  Put_Line("Usuario" & Integer'Image(ClienteID) & " sale de la cola de espera.");
                  Primero := (Primero mod MaxCola) + 1;
                  EnEspera := EnEspera - 1;
               end;
         end select;
      end loop;
   end Cola;


task Generador;

task body Generador is
   ID : Integer := 0;
   Esperados : Integer;
begin
   Put("Ingrese la cantidad de personas a crear: ");
   Get(Esperados);

   while ID < Esperados loop
      ID := ID + 1;
      select
         Cola.Entrar(ID);
      or
         delay 3.0;
         ID := ID - 1; -- Si no puede entrar, reintenta
      end select;

      delay 1.0;  -- Una persona por segundo
   end loop;
end Generador;


   task type Caja(ID : Integer);

   task body Caja is
      ClienteID : Integer;
   begin
      loop
         Cola.Salir(ClienteID);

         Put_Line("Persona" & Integer'Image(ClienteID) & " ingresó a la caja" & Integer'Image(ID));

         declare
            Tiempo : Duration := Duration(Rand.Random(Gen) * 5.0);
         begin
            delay Tiempo;
         end;

         Put_Line("Persona" & Integer'Image(ClienteID) & " saliendo de la caja" & Integer'Image(ID));
      end loop;
   end Caja;


   C1 : Caja(1);
   C2 : Caja(2);
   C3 : Caja(3);
   C4 : Caja(4);

begin
   Rand.Reset(Gen);
   null; 
end Main;

