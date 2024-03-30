#!/bin/bash
sudo clear
#Reason for sudo = enter password first
#Run this in the build folder!!!
#Credits to:
#0xAgartha - https://www.unknowncheats.me/forum/members/5290135.html
#ghostrazzor - https://www.unknowncheats.me/forum/members/2764232.html
 
# Get the directory where the script is executed from
script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
 
# Original binary directory is in /build folder
original_binary_dir="$script_dir"
 
# Original binary name
original_binary_name="zapclient"
 
# Log file directory is the same as the script directory
log_dir="$script_dir"
 
# Log file path
log_file="$log_dir/script_log.txt"
 
# Function to log messages
log() {
    echo "$(date +"%Y-%m-%d %H:%M:%S") - $1" >> "$log_file"
}
 
# Create log file
mkdir -p "$log_dir"
touch "$log_file"
 
# Log script start
log "Script started"
 
# Generate a random number for the name length
random_width=$((5 + RANDOM % 11))
 
# Generate a random name for the temporary binary
random_name=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w $random_width | head -n 1)
 
# Temporary path for the temporary binary with the new name
temp_binary_path="/tmp/$random_name"
 
# Copy the original binary to the new path (to keep the original intact)
if ! cp "$original_binary_dir/$original_binary_name" "$temp_binary_path"; then
    log "Failed to copy binary: $original_binary_dir/$original_binary_name to $temp_binary_path"
    exit 1
fi
log "Binary copied: $original_binary_dir/$original_binary_name to $temp_binary_path"
 
# Execute the binary under the new name
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
echo "Executing $original_binary_name"
sleep 0.5
sudo "$temp_binary_path" &
pid=$! # Get the PID of the executed binary
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
    log "Failed to execute binary with PID: $pid"
    exit 1
fi
log "Binary execution completed"
 
# Delete the temporary binary after execution
if ! rm "$temp_binary_path"; then
    log "Failed to delete temporary binary: $temp_binary_path"
else
    log "Temporary binary deleted: $temp_binary_path"
fi
 
# Log script end
log "Script completed"
