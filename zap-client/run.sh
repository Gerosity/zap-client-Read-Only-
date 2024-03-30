#!/bin/bash
sudo clear
#Run this in the build folder!!!
#Credits to:
#0xAgartha - https://www.unknowncheats.me/forum/members/5290135.html
#ghostrazzor - https://www.unknowncheats.me/forum/members/2764232.html
 
# Function to handle errors
handle_error() {
    echo "Error: $1"
    exit 1
}
 
# Main directory path is where the script is executed
script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
 
# Log file path in the main directory
log_file="$script_dir/script_log.txt"
 
# Function to log messages
log() {
    echo "$(date +"%Y-%m-%d %H:%M:%S") - $1" >> "$log_file" || handle_error "Failed to write to log file: $log_file"
}
 
# Create log file directory if it doesn't exist
mkdir -p "$script_dir" || handle_error "Failed to create log directory: $script_dir"
 
# Log script start
log "Script started"
 
# Original binary name
original_binary_name="zapclient"
 
# Generate a random name for the temporary binary
temp_binary_name=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 10 | head -n 1)
 
# Temporary path for the temporary binary
temp_binary_path="/$script_dir/$temp_binary_name"
 
# Copy the original binary to the temporary path
if ! cp "$script_dir/$original_binary_name" "$temp_binary_path"; then
    log "Failed to copy binary: $script_dir/$original_binary_name to $temp_binary_path"
    exit 1
fi
log "Binary copied: $script_dir/$original_binary_name to $temp_binary_path"
 
# Log the binary being executed
log "Executing binary: $temp_binary_name"

# Credits and such
sleep 1
echo "Run Script For zap-client"
sleep 1
echo "Credits to: "
sleep 0.5
echo "0xAgartha - https://www.unknowncheats.me/forum/members/5290135.html"
sleep 0.2
echo "ghostrazzor - https://www.unknowncheats.me/forum/members/2764232.html"
sleep 1
echo "-----------------------------------------------------------------------"
#Shit way of adding a separator but sorry not sorry
echo "Executing $original_binary_name as $temp_binary_name"
sleep 0.5

# Execute the binary
(sudo "./$temp_binary_name") & pid=$! # Get the PID of the executed binary
log "Binary executed with PID: $pid"
 
# Hide the PID of the executed binary and its child processes
if echo "$pid" | sudo tee /proc/sys/kernel/ns_last_pid > /dev/null; then
    log "Process ID $pid hidden successfully"
    
    # Hide child process PIDs
    child_pids=$(pgrep -P $pid)
    for child_pid in $child_pids; do
        if echo "$child_pid" | sudo tee /proc/sys/kernel/ns_last_pid > /dev/null; then
            log "Child process ID $child_pid hidden successfully"
        else
            log "Failed to hide child process ID $child_pid"
        fi
    done
else
    log "Failed to hide process ID $pid"
fi
 
# Wait for the binary to finish execution
if ! wait $pid; then
    #log "Failed to execute binary with PID: $pid"
    log "Deleting binary with PID: $pid"
    rm "$temp_binary_name"
    exit 1
fi
 
log "Binary execution completed"
 
# Log script end
log "Script completed"
