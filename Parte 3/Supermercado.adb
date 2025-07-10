with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with Ada.Numerics.Discrete_Random;
with Ada.Numerics.Float_Random;

procedure Main is
   MaxCola      : constant Integer := 10;
   NumCajas     : constant Integer := 4;
   TotalClientes : Integer := 0;
   ClientesAtendidos : Integer := 0;
   
   subtype Rango is Integer range 0 .. 5000;  --esto es para el tiempo de espera
   package Rand_Int is new Ada.Numerics.Discrete_Random(Rango);
   Gen : Rand_Int.Generator;
   Float_Gen : Ada.Numerics.Float_Random.Generator;

   task Cola is
      entry Entrar(ID : Integer);
      entry Salir(ClienteID : out Integer);
      entry Consultar_Estado(Esperando : out Integer);
      entry Cliente_Atendido;
   end Cola;

   task body Cola is
      EnCola: array(1 .. MaxCola) of Integer; --array circular
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
         or
            accept Consultar_Estado(Esperando : out Integer) do
               Esperando := EnEspera;
            end;
         or
            accept Cliente_Atendido do
               ClientesAtendidos := ClientesAtendidos + 1;
            end;
         end select;
      end loop;
   end Cola;

   task Generador;
   task body Generador is
      ID : Integer := 0;
      Esperados : Integer;
      Tiempo_Espera : Float;
      Personas_Esperando : Integer;
   begin
      Put("Ingrese la cantidad de personas a crear: ");
      Get(Esperados);
      TotalClientes := Esperados;
      
      while ID < Esperados loop
         ID := ID + 1;
         
         Cola.Consultar_Estado(Personas_Esperando);
         if Personas_Esperando > 0 then
            Put_Line("Hay" & Integer'Image(Personas_Esperando) & " personas esperando en la cola.");
         end if;
         
         loop
            select
               Cola.Entrar(ID);
               exit;
            else
               Put_Line("Cola de espera llena, no se permiten más personas por ahora.");
               Tiempo_Espera := Ada.Numerics.Float_Random.Random(Float_Gen) * 3.0;
               delay Duration(Tiempo_Espera);
            end select;
         end loop;
         delay 1.0; 
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
         Cola.Cliente_Atendido;
         
         if ClientesAtendidos >= TotalClientes then
            exit;
         end if;
      end loop;
   end Caja;

   C1 : Caja(1);
   C2 : Caja(2);
   C3 : Caja(3);
   C4 : Caja(4);

begin
   Rand_Int.Reset(Gen); --inicializa el generador de números aleatorios
   Ada.Numerics.Float_Random.Reset(Float_Gen); 

   loop
      delay 1.0;
      exit when TotalClientes > 0 and then ClientesAtendidos >= TotalClientes;
   end loop;
   
   Put_Line("Todos los clientes fueron atendidos. Terminando programa.");
end Main;