with Ada.Text_IO; use Ada.Text_IO;  -- Para leer y escribir en consola
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;  -- Para manejar enteros
with Ada.Numerics.Discrete_Random;  -- Para números aleatorios enteros

procedure Main is
   -- Definimos las constantes
   MaxCola      : constant Integer := 10;
   NumCajas     : constant Integer := 4;
   TotalClientes : Integer;

   -- Para el tiempo aleatorio de las cajas (0 a 5000 ms)
   subtype Rango is Integer range 0 .. 5000;
   package Rand_Int is new Ada.Numerics.Discrete_Random(Rango);
   Gen : Rand_Int.Generator;

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
         select
            when EnEspera < MaxCola =>
               accept Entrar(ID : Integer) do
                  Ultimo := (Ultimo mod MaxCola) + 1;
                  EnCola(Ultimo) := ID;
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
         loop
            select
               Cola.Entrar(ID);
               exit;
            else
               delay 3.0;
               ID := ID - 1;  -- Reintentar con mismo ID
            end select;
         end loop;

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
            R : Integer := Rand_Int.Random(Gen);
            Tiempo : Duration := Duration(Float(R) / 1000.0);
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
   Rand_Int.Reset(Gen);
   null;
end Main;