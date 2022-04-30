class RPNToAssembly {
  final String prefix = "main:\nldi r16, 0b1111111\nout DDRB, r16\n\nstart:";
  final String sufix = "\nout PORTB, r16\nrjmp start";

  String rpnSumToAssembly(String firstNumber, String secondNumber) {
    final String ldi1 = "ldi r16,";
    final String ldi2 = "ldi r17,";
    final add = "add r16, r17";

    return "$prefix$ldi1$firstNumber\n$ldi2$secondNumber\n$add$sufix";
  }
}
