pipeline {
  agent any
  stages {
    stage('checkout code') {
      steps {
        git(url: 'https://github.com/aakashk49/CMH-OR', branch: 'main')
      }
    }

    stage('list files') {
      parallel {
        stage('list files') {
          steps {
            sh 'ls -la'
          }
        }

        stage('Build program') {
          steps {
            sh 'cd . && g++ CMH_OR.cpp'
          }
        }

      }
    }

  }
}