import socket

# Indirizzo IP e porta del server sull'Arduino
arduino_ip = '192.168.43.227'  # Cambia questo con l'IP dell'Arduino
arduino_port = 8888  # Cambia questo con la porta del server sull'Arduino

def main():
    while True:
        try:
            # Creazione del socket TCP
            client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            
            # Connessione al server sull'Arduino
            client_socket.connect((arduino_ip, arduino_port))
            
            # Dati da inviare all'Arduino
            data = input("-> ")  # Cambia questo con i dati che vuoi inviare
            
            
            # Invio dei dati
            if data in ["W","A","D","S","Q"]:
                client_socket.sendall(data.encode())
            
            if data.lower() == 'exit':
                print("Chiusura del client.")
                break
            
        except ConnectionRefusedError:
            print("Connessione rifiutata. Verifica che l'Arduino sia accesso e connesso correttamente.")
            break
        except socket.error as e:
            print(f"Errore di socket: {e}")
            break
        finally:
            # Chiusura del socket
            client_socket.close()

if __name__ == "__main__":
    main()
