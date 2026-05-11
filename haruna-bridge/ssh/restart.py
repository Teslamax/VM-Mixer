import subprocess

def restart_service(host, service):
    subprocess.run([
        "ssh",
        host,
        "sudo",
        "systemctl",
        "restart",
        service
    ], check=True)
