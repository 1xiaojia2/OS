def generateText(s, count):
    result = ''
    for num in range(count):
        new_str = s.replace('@', str(num))
        result += new_str + '\n'
    print(result)


def main():
    s = "set_idt_entry(@, _isr_stub_@, 0x08, IDT_INTR_ACCESS_DPL0);"
    count = 32
    generateText(s, count)

if __name__ == "__main__":
    main()