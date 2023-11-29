﻿// Copyright (c) Microsoft Corporation
// The Microsoft Corporation licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.

using System;
using System.IO;
using System.IO.Abstractions;
using System.Threading.Tasks;

namespace Microsoft.FancyZonesEditor.UITests.Utils
{
    public class IOTestHelper
    {
        private readonly IFileSystem _fileSystem = new FileSystem();

        private string _fileName;

        private string _data = string.Empty;

        public IOTestHelper(string fileName)
        {
            _fileName = fileName;

            if (_fileSystem.File.Exists(_fileName))
            {
                _data = ReadFile(_fileName);
            }
        }

        public void RestoreData()
        {
            if (_data != string.Empty)
            {
                WriteData(_data);
            }
            else
            {
                DeleteFile();
            }
        }

        public void WriteData(string data)
        {
            var attempts = 0;
            while (attempts < 10)
            {
                try
                {
                    _fileSystem.File.WriteAllText(_fileName, data);
                }
                catch (Exception)
                {
                    Task.Delay(10).Wait();
                }

                attempts++;
            }
        }

        private string ReadFile(string fileName)
        {
            var attempts = 0;
            while (attempts < 10)
            {
                try
                {
                    using (Stream inputStream = _fileSystem.File.Open(fileName, FileMode.Open))
                    using (StreamReader reader = new StreamReader(inputStream))
                    {
                        string data = reader.ReadToEnd();
                        inputStream.Close();
                        return data;
                    }
                }
                catch (Exception)
                {
                    Task.Delay(10).Wait();
                }

                attempts++;
            }

            return string.Empty;
        }

        public void DeleteFile()
        {
            var attempts = 0;
            while (attempts < 10)
            {
                try
                {
                    _fileSystem.File.Delete(_fileName);
                }
                catch (Exception)
                {
                    Task.Delay(10).Wait();
                }

                attempts++;
            }
        }
    }
}