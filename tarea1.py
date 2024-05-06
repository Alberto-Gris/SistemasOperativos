"""
# Mini-Shell en Python3
#
# Aragón Toledo José Ramón
# García Ramírez Fernando
# Hernández Gris Alberto
#
# Grupo 602-A
"""

import os
import sys
import subprocess

def ejecutar_comando(comando, datos_entrada=None):
    """
    Ejecuta un comando en el shell con la posibilidad de pasarle datos de entrada.
    
    :param comando: El comando a ejecutar como una cadena.
    :param datos_entrada: Datos opcionales de entrada para el comando.
    :return: Una tupla que contiene la salida estándar y el error estándar del comando ejecutado.
    """
    try:
        if datos_entrada:
            # subprocess.Popen lanza un proceso. Los argumentos stdin, stdout, y stderr especifican cómo se deben manejar los flujos correspondientes
            # stdin=subprocess.PIPE permite enviar datos al proceso. stdout y stderr capturan la salida y el error del proceso, respectivamente.
            proc = subprocess.Popen(comando, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

            # communicate() interactúa con el proceso; envía datos a stdin (si se especifica) y lee stdout y stderr hasta que finaliza el proceso.
            # input=datos_entrada.encode() convierte la cadena de entrada a bytes, necesarios para enviar a través de stdin.
            stdout, stderr = proc.communicate(input=datos_entrada.encode())
        else:
            # Si no hay datos de entrada, simplemente se ejecuta el comando y se capturan su salida y error estándar.
            proc = subprocess.Popen(comando, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            stdout, stderr = proc.communicate()

        # Decodifica los bytes capturados a una cadena UTF-8 para su uso en Python.
        return stdout.decode(), stderr.decode()
    except Exception as e:
        # En caso de error, se captura y se devuelve el mensaje de error.
        return None, str(e)

def analizar_comando(comando): 
    """
    Divide el comando de entrada en subcomandos basados en el carácter de tubería '|' para soportar la funcionalidad de piping.
    
    :param comando: El comando de entrada como cadena.
    :return: Una lista de comandos individuales a ejecutar en secuencia.
    """
    # Divide el comando completo en partes donde encuentra '|', y elimina espacios en blanco alrededor de cada parte.
    comandos = comando.split('|')
    comandos = [cmd.strip() for cmd in comandos]
    return comandos

def principal():
    """
    Función principal que ejecuta un bucle interactivo para aceptar comandos del usuario, procesarlos y ejecutarlos.
    """
    print("\nNOTA: Los archivos creados y leidos se tomarán del directorio desde donde se ejecutó el mini-shell (no necesariamente donde está guardado).\n")
    while True:
        try:
            entrada_usuario = input("tarea1$:> ").strip()  # Solicita entrada del usuario.
            if not entrada_usuario:  # Continúa el bucle si la entrada está vacía.
                continue
            comandos = analizar_comando(entrada_usuario)  # Divide la entrada en comandos individuales para ejecutar.
            num_comandos = len(comandos)
           
            if num_comandos == 1:
                # Casos de redireccionamiento de salida ('>' y '>>') y entrada ('<').
                if '<' in comandos[0]:
                    # Busca si debe redireccionar la salida, además de la entrada
                    if '>>' in comandos[0]:
                        parte1, parte2 = comandos[0].split('<') # Separa la instrucción en el operando de concatenación
                        # Asigna las partes necesarias (comando, archivo_entrada, archivo_salida)
                        if '>>' in parte1:
                            comando, archivo_salida = parte1.split('>>')
                            archivo_entrada = parte2
                        else:
                            archivo_entrada, archivo_salida = parte2.split('>>')
                            comando = parte1
                        # Recibe datos del archivo de entrada y escribe el resultado en el archivo de salida
                        with open(archivo_entrada.strip(), 'r') as a_e:
                            datos_entrada = a_e.read()   # Lee los datos del archivo especificado para usarlos como entrada del comando.
                        stdout, stderr = ejecutar_comando(comando.strip(), datos_entrada)
                        if stdout:
                            with open(archivo_salida.strip(), 'a') as a_s:
                                a_s.write(stdout)
                    elif '>' in comandos[0]:
                        parte1, parte2 = comandos[0].split('<') # Separa la instrucción en el operando de lectura
                        # Asigna las partes necesarias (comando, archivo_entrada, archivo_salida)
                        if '>' in parte1:
                            comando, archivo_salida = parte1.split('>')
                            archivo_entrada = parte2
                        else:
                            archivo_entrada, archivo_salida = parte2.split('>')
                            comando = parte1
                        # Recibe datos del archivo de entrada y concatena el resultado al archivo de salida
                        with open(archivo_entrada.strip(), 'r') as a_e:
                            datos_entrada = a_e.read()   # Lee los datos del archivo especificado para usarlos como entrada del comando.
                        stdout, stderr = ejecutar_comando(comando.strip(), datos_entrada)
                        if stdout:
                            with open(archivo_salida.strip(), 'w') as a_s:
                                a_s.write(stdout)
                    else:
                        comando, archivo_entrada = comandos[0].split('<')
                        with open(archivo_entrada.strip(), 'r') as f:
                            datos_entrada = f.read()  # Lee los datos del archivo especificado para usarlos como entrada del comando.
                        stdout, stderr = ejecutar_comando(comando.strip(), datos_entrada)
                        print(stdout)  # Imprime la salida del comando.
                elif '>>' in comandos[0]:
                    comando, archivo_salida = comandos[0].split('>>')
                    stdout, stderr = ejecutar_comando(comando.strip())
                    if stdout:
                        with open(archivo_salida.strip(), 'a') as f:
                            f.write(stdout)   # Concatena la salida del comando con el contenido del archivo especificado.
                elif '>' in comandos[0]:
                    comando, archivo_salida = comandos[0].split('>')
                    stdout, stderr = ejecutar_comando(comando.strip())
                    if stdout:
                        with open(archivo_salida.strip(), 'w') as f:
                            f.write(stdout)  # Escribe la salida del comando en el archivo especificado.
                else:
                    if (comandos[0]=="exit"):
                        print("Saliendo...")
                        break      # Si el comando ejecutado es 'exit', termina el mini-shell
                    stdout, stderr = ejecutar_comando(comandos[0])
                    print(stdout)  # Imprime la salida del comando.
            else:
                # Manejo de piping entre múltiples comandos.
                procesos = []
                for i in range(num_comandos):
                    # El primer comando no recibe entrada de otro proceso. Los siguientes usan la salida del anterior como su entrada.
                    if i == 0:
                        procesos.append(subprocess.Popen(comandos[i].split(), stdout=subprocess.PIPE))
                    else:
                        procesos.append(subprocess.Popen(comandos[i].split(), stdin=procesos[i-1].stdout, stdout=subprocess.PIPE))
                
                # Espera a que todos los procesos finalicen.
                for proc in procesos:
                    proc.wait()
                
                # Cierra los flujos de salida de todos los procesos excepto el último para evitar bloqueos o fugas de recursos.
                for proc in procesos[:-1]:
                    proc.stdout.close()
                
                # Imprime la salida del último proceso en la cadena de comandos.
                print(procesos[-1].communicate()[0].decode())
        except KeyboardInterrupt:
            # Manejo de interrupción del programa por el usuario (Ctrl+C).
            print("\nSaliendo...")
            break
        except Exception as e:
            # Captura de cualquier otra excepción y muestra el mensaje de error.
            print("Se produjo un error:", e)

if __name__ == "__main__":
    principal()
