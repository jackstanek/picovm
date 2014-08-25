#ifndef _OPCODE_H
#define _OPCODE_H

/* This file defines the opcodes for our virtual machine.
 * The calling conventions for the opcodes is as follows:
 * <op> <arg> <arg> <arg>. Where applicable, this format can also
 * be expressed as <op> <src> <dst> NOP. (For instance, MOV)
 * All ops are represented in byte code programs in binary
 * representations. Any operations which require less than a
 * 4 byte representation should be padded with NOP until 4 bytes
 * are consumed. */

#define NOP 0x00		/* No operation */

#define ADD 0x01 		/* Add two registers */
#define SUB 0x02		/* Subtract two registers */
#define MUL 0x03		/* Multiply two registers */
#define DIV 0x04		/* Divide two registers */

#define MOV 0x05		/* Copy contents of one register to another */
#define LOD 0x06		/* Load data from mem address to register */
#define STO 0x07		/* Store data from reg to mem */
#define SET 0x08		/* Sets the register to a specific value */

#define PRI 0x09		/* Print the register to vm's stdout */
#define ERR 0x0A		/* Print the register to stderr */

#endif
