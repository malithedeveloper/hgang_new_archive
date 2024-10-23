void processWriteFile(WRITE_FILE_REQUEST* request) {
	NTSTATUS status;

	HANDLE hFile;
	status = createFile(request->kernelPath, &hFile);
	if (!NT_SUCCESS(status)) {
		request->status = status;
		return;
	}

	PFILE_OBJECT pFileObject;
	status = ObReferenceObjectByHandleWithTag(hFile, SYNCHRONIZE, *IoFileObjectType,
		KernelMode, 'eliF', (PVOID*)&pFileObject, NULL);
	if (!NT_SUCCESS(status)) {
		request->status = status;
		ObCloseHandle(hFile, KernelMode);
		return;
	}

	pFileObject->Busy = FALSE;
	pFileObject->DeletePending = FALSE;
	pFileObject->SharedWrite = TRUE;
	pFileObject->WriteAccess = TRUE;

	LARGE_INTEGER writeOffset;
	writeOffset.QuadPart = 0;

	PDEVICE_OBJECT pFileDevice = IoGetBaseFileSystemDeviceObject(pFileObject);

	IO_STATUS_BLOCK ioStatus = { 0 };
	PIRP pIrp = IoBuildAsynchronousFsdRequest(IRP_MJ_WRITE, pFileDevice,
		request->content, request->length, &writeOffset, &ioStatus);
	IoSetCompletionRoutine(pIrp, defaultCompletionRoutine, NULL, TRUE, TRUE, TRUE);

	KEVENT completionEvent;
	KeInitializeEvent(&completionEvent, SynchronizationEvent, FALSE);

	PIO_STACK_LOCATION pIrpStack = IoGetNextIrpStackLocation(pIrp);
	pIrp->RequestorMode = KernelMode;
	pIrp->UserEvent = &completionEvent;
	pIrpStack->Flags |= SL_FORCE_DIRECT_WRITE;

	status = IofCallDriver(pFileDevice, pIrp);
	KeWaitForSingleObject(&completionEvent, Executive, KernelMode, TRUE, NULL);
	if (NT_SUCCESS(status)) {
		status = sendEndOfFile(pFileObject, request->length);
	}
		
	ObfDereferenceObject(pFileObject);
	ObCloseHandle(hFile, KernelMode);
	request->status = status;
}