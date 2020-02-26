// CPU class for 6502
// Example taken from: http://c64-retro-coding.blogspot.com/p/writing-6502-emulator-in-net.html
// Credit: http://c64-retro-coding.blogspot.com/p/writing-6502-emulator-in-net.html
using System;
using System.Collections.Generic;
using System.Text;

namespace _6502Emulator
{
    public class CPU
    {
        private bool _isExecuting;
        private byte[] _romKernel;
        private byte[] _romBasic;
        private UInt16 _stackPtr;
        // 
        private byte _sp;
        // status register
        private byte _sr;

        public Dictionary<string, byte> OpCodes { get; set; }
        // Program Counter
        public UInt16 PC { get; set; }
        // Ram
        public byte[] Ram { get; set; }
        // A Register
        public byte RegA{ get; set; }
        // X Regsiter
        public byte RegX{ get; set; }
        // Y Register
        public byte RegY { get; set; }

        public bool Z
        {
            // Zero-Flag (bit 1)
            get { return ((_sr & 2) == 2); }
        }
        public bool C 
        {
            // Carry-Flag (bit 0)
            get { return ((_sr & 1) == 1); }
        }
        public bool N 
        {
            // Negative-Flag (bit 7)
            get { return ((_sr & 128) == 128); }
        }
        public bool V 
        {
            // Overflow-Flag (bit 6)
            get { return ((_sr & 8) == 8); }
        }
        public bool B 
        {
            // Break-Flag (bit 4)
            get { return ((_sr & 16) == 16); }
        }
        public bool D 
        {
            // Decimal-Flag (bit 3)
            get { return ((_sr & 8) == 8); }
        }
        public bool I 
        {
            // Interrupt-Flag (bit 2)
            get { return ((_sr & 4) == 4); }
        }

        public CPU()
        {
            OpCodes = new Dictionary<string, byte>();
            Initialize();   
        }

        private void Execute(byte opCode)
        {
            byte low;
            byte high;

            switch (opCode)
            {
                // LDA immediate addressing
                case 0xA9:
                    RegA = GetNextMem();
                    break;

                // STA absolute addressing
                // a register
                case 0x8D:
                    // get the address location to store
                    low = GetNextMem();
                    high = GetNextMem();

                    // write to memory
                    // need to left-shift the high byte by 8 bits and add the low byte to get the 16-bit address
                    MemoryWrite((UInt16)(high << 8 | low), RegA);
                    break;

                // STX absolute addressing
                // x register
                case 0x8E:
                    // get the address location to store
                    low = GetNextMem();
                    high = GetNextMem();

                    // write to memory
                    // need to left shift the high byte by 8 bits and add the low byte to get the 16-bit address
                    MemoryWrite((UInt16)(high << 8 | low), RegX);
                    break;

                // STY absolute addressing
                // y register
                case 0x8F:
                    // get the address location to store
                    low = GetNextMem();
                    high = GetNextMem();

                    // write to memory
                    // need to left shift the high byte by 8 bits and add the low byte to get the 16-bit address
                    MemoryWrite((UInt16)(high << 8 | low), RegY);
                    break;

                // PHA push accumulator
                case 0x48:
                    // push the contents of the accumulator onto the stack
                    PushStack(RegA);
                    break;

                // PHP push status register (SR)
                case 0x08:
                    // push the contents of the SR onto the stack
                    PushStack(_sr);
                    break;
                case 0x00:
                // drop through, this signals end of program

                default:
                    _isExecuting = false;
                    break;
            }
        }

        private byte GetNextMem()
        {
            // get the next address in memory
            return (byte)Ram[PC++];
        }

        private void Initialize()
        {
            // ram is 64k 0xFFFF
            Ram = new byte[0xFFFF];

            // init rom
            _romKernel = new byte[8192];
            _romBasic = new byte[8192];

            // stack is 256 byte stored at $0100-$01FF (starts at $01FF or 0x01FF)
            _stackPtr = 0x01FF;

            // program counter starts at $0 or, the first memory location
            PC = 0x00;
        }

        private byte MemoryRead(UInt16 address)
        {
            // read from RAM
            return (byte)Ram[address];
        }

        private void MemoryWrite(UInt16 address, byte value)
        {
            // write to RAM
            Ram[address] = value;
        }

        private byte PopStack()
        {
            // pop from SP
            byte value = MemoryRead(_stackPtr);

            // if stack is greater than 0x01FF, set to 0x01FF so it's within bounds of stack (0x0100 to 0x01FF), starting at 0x01FF
            if (_stackPtr > 0x01FF)
                _stackPtr = 0x01FF;
            return value;
        }

        private void PushStack(byte value)
        {
            // push to SP
            Ram[_stackPtr--] = value;    // stack starts at 0x01FF and moves down (to 0x0100)

            // when stack is less than 0x0100, reset it to the top of the stack because that indicates an empty stack
            if (_stackPtr < 0x0100)
                _stackPtr = 0x01FF;
        }

        public void Run()
        {
            _isExecuting = true;

            while(_isExecuting)
            {
                // fetch next opcode
                byte opCode = Ram[PC++];

                Execute(opCode);
            }
        }
    }
}
