  int64_t pos;
  FFmpegURLProtocol* prot = reinterpret_cast<FFmpegURLProtocol*>(opaque);
  AVIOContext* pCtx =
      (AVIOContext*)(((char*)opaque) - offsetof(AVIOContext, opaque));
  pos = pCtx->pos;
  prot->GetPosition(&pos);
  int ret = prot->Read(buf_size, buf);
  // prot->GetPosition(&pos);
  // pos = pCtx->pos;
  std::string file = "Z:\\Desktop\\nnn\\";
  CreateDirectoryA(file.c_str(), NULL);
  // file += std::to_string(base::PlatformThread::CurrentId());
  // file += "-";
  file += std::to_string(reinterpret_cast<uint64_t>(opaque));
  // file += "AAA.mp4";

  HANDLE hFile = CreateFileA(file.c_str(), GENERIC_WRITE, 
	  FILE_SHARE_READ, NULL, OPEN_ALWAYS,
      FILE_ATTRIBUTE_NORMAL | FILE_FLAG_RANDOM_ACCESS, NULL);
  DWORD dw = SetFilePointer(hFile, pos, NULL, FILE_BEGIN);
  WriteFile(hFile, buf, ret, &dw, NULL);
  FlushFileBuffers(hFile); 
  CloseHandle(hFile);
  //FILE* f = fopen(file.c_str(), "wb");
  //int a = fseek(f, (long)(pos), SEEK_SET);
  //a = fwrite(buf, 1, ret, f);
  //fclose(f);

  return ret;
