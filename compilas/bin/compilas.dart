import 'dart:async';
import 'dart:io';
import 'dart:convert';
import 'package:tuple/tuple.dart';

import 'RPN_to_ASM.dart';

final RPNToAssembly rpnToAssembly = RPNToAssembly();
void main(List<String> arguments) {
  openFile().then((content) {
    LineSplitter splitter = LineSplitter();
    List<String> contentLines = splitter.convert(content);
    String assemblyText = "";
    Operation operation = Operation.none;

    contentLines.forEach((String line) {
      final Tuple2<String, Operation> result = generateAssembly(line);
      writeFile(result.item1, result.item2);
    });
  });
}

Future<String> openFile() async {
  var myFile = File('RPN.txt');
  return await myFile.readAsString();
}

Tuple2<String, Operation> generateAssembly(String line) {
  String assemblyText = "";
  Operation operation = Operation.none;

  line.runes.forEach((int rune) {
    var char = String.fromCharCode(rune);
    switch (char) {
      case '+':
        assemblyText = rpnToAssembly.rpnSumToAssembly(line[0], line[2]);
        operation = Operation.sum;
        break;
      case '*':
        assemblyText = rpnToAssembly.rpnSumToAssembly(line[0], line[2]);
        operation = Operation.mul;
        break;
      case '-':
        assemblyText = rpnToAssembly.rpnSumToAssembly(line[0], line[2]);
        operation = Operation.sub;
        break;
      case '/':
        assemblyText = rpnToAssembly.rpnSumToAssembly(line[0], line[2]);
        operation = Operation.div;
        break;
    }
  });

  return Tuple2(assemblyText, operation);
}

void writeFile(String assemblyText, Operation operation) {
  String fileName = "";

  switch (operation) {
    case Operation.sum:
      fileName = 'SUM.txt';
      break;
    case Operation.sub:
      fileName = 'SUB.txt';
      break;
    case Operation.mul:
      fileName = 'MUL.txt';
      break;
    case Operation.div:
      fileName = 'DIV.txt';
      break;
    case Operation.pot:
      fileName = 'POT.txt';
      break;
    case Operation.rest:
      fileName = 'REST.txt';
      break;
  }
  File(fileName).writeAsString(assemblyText);
}

enum Operation {
  sum,
  sub,
  mul,
  div,
  pot,
  rest,
  none,
}
