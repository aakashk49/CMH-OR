pipeline {
  agent any
  stages {
    stage('checkout code') {
      steps {
        git(url: 'https://github.com/aakashk49/CMH-OR', branch: 'main')
      }
    }

    stage('List') {
      parallel {
        stage('List') {
          steps {
            sh 'ls -la'
          }
        }

        stage('build') {
          steps {
            sh 'g++ *.cpp && ls -la'
          }
        }

      }
    }

  }
}