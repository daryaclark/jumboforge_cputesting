# author: darya clark
# purpose: parser used to take in data after running 'top -d -b 1' and output
#          csv file 

import re
import csv

def extract_cpu_ram_numbers(line):
    # match to pattern of current top command
    pattern = r"3507\s+3477\s+apps\s+S\s+\d+\s+(\d+)%\s+(\d+)%\s+.+"
    match = re.search(pattern, line)
    if match:
        cpu_usage = int(match.group(2))
        print(cpu_usage)
        return cpu_usage
    else:
        return None

def main(input_file, output_file):
    with open(input_file, 'r') as f:
        lines = f.readlines()

    with open(output_file, 'w', newline='') as csvfile:
        csv_writer = csv.writer(csvfile)
        csv_writer.writerow(['CPU Usage'])

        for line in lines:
            print("working")
            cpu = extract_cpu_ram_numbers(line)
            if cpu is not None:
                csv_writer.writerow([cpu])

if __name__ == "__main__":
    # Provide the path to your input file here
    input_file = 'discovery1' 
    # Provide the path to your output CSV file here 
    output_file = 'apMultiMarioOdom5.csv'  
    main(input_file, output_file)
