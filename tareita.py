import os
import sys
import subprocess

def execute_command(command, input_data=None):
    try:
        if input_data:
            proc = subprocess.Popen(command, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            stdout, stderr = proc.communicate(input=input_data.encode())
        else:
            proc = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            stdout, stderr = proc.communicate()
        return stdout.decode(), stderr.decode()
    except Exception as e:
        return None, str(e)

def parse_command(command):
    commands = command.split('|')
    commands = [cmd.strip() for cmd in commands]
    return commands

def main():
    while True:
        try:
            user_input = input("$:> ").strip()
            if not user_input:
                continue
            commands = parse_command(user_input)
            num_commands = len(commands)
            
            if num_commands == 1:
                if '>' in commands[0]:
                    command, output_file = commands[0].split('>')
                    command = command.strip()
                    output_file = output_file.strip()
                    stdout, stderr = execute_command(command)
                    if stdout:
                        with open(output_file, 'w') as f:
                            f.write(stdout)
                elif '<' in commands[0]:
                    command, input_file = commands[0].split('<')
                    command = command.strip()
                    input_file = input_file.strip()
                    with open(input_file, 'r') as f:
                        input_data = f.read()
                    stdout, stderr = execute_command(command, input_data)
                    print(stdout)
                else:
                    stdout, stderr = execute_command(commands[0])
                    print(stdout)
            else:
                processes = []
                for i in range(num_commands):
                    if i == 0:
                        processes.append(subprocess.Popen(commands[i].split(), stdout=subprocess.PIPE))
                    elif i == num_commands - 1:
                        processes.append(subprocess.Popen(commands[i].split(), stdin=processes[i-1].stdout, stdout=subprocess.PIPE))
                    else:
                        processes.append(subprocess.Popen(commands[i].split(), stdin=processes[i-1].stdout, stdout=subprocess.PIPE))
                for proc in processes:
                    proc.wait()
                for proc in processes[:-1]:
                    proc.stdout.close()
                print(processes[-1].communicate()[0].decode())
        except KeyboardInterrupt:
            print("\nExiting...")
            break
        except Exception as e:
            print("An error occurred:", e)

if __name__ == "__main__":
    main()