pipeline {
  agent any
  stages {
    stage('install git') {
      steps {
        sh 'sudo apt install git'
      }
    }

    stage('checkout code') {
      steps {
        git(url: 'https://github.com/aakashk49/NAND2Tetris-Assembler', branch: 'main')
      }
    }

    stage('List') {
      steps {
        sh 'ls -la'
      }
    }

  }
}