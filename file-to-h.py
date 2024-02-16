import argparse

def file_to_hex_array(file_path):
    try:
        with open(file_path, 'rb') as file:
            byte_array = file.read()
            hex_array = ['0x{:02x}'.format(byte) for byte in byte_array]
            return hex_array
    except FileNotFoundError:
        print("Error: File not found.")
        return None

def main():
    parser = argparse.ArgumentParser(description='Convert files into C headers')
    parser.add_argument('file', metavar='file_path', type=str, help='path to the file')
    parser.add_argument('name', metavar='name', type=str, help='name of file')
    args = parser.parse_args()

    count = 0
    hex_array = file_to_hex_array(args.file)
    args.name = args.name.upper()

    print(f"#ifndef _H_FILE_{args.name}")
    print(f"#define _H_FILE_{args.name}")
    print("#pragma GCC diagnostic push")
    print("#pragma GCC diagnostic ignored \"-Woverflow\"")
    print("#pragma clang diagnostic push")
    print("#pragma clang diagnostic ignored \"-Woverflow\"")

    print(f"const int FILE_{args.name}_size = {len(hex_array)};")
    print(f"const unsigned char FILE_{args.name}[{len(hex_array)}] = {{")
    print("    ", end="");
    while True:
        if count >= 16:
            print("\n    ", end="");
            count = 0

        if len(hex_array) <= 1:
            print(f"{hex_array.pop(0)}\n}};");
            break;
        print(f"{hex_array.pop(0)}, ", end="");
        count += 1;
    
    print("#pragma GCC diagnostic pop")
    print("#pragma clang diagnostic pop")
    print("#endif")

if __name__ == "__main__":
    main()