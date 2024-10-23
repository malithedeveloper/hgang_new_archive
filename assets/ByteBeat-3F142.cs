using System;
using System.IO;
using System.Media;

public class ByteBeat
{
	private bool _isstopped = false;
	
	private void Load(int channel, int rate, int bps, int timeline, byte[] data)
	{
		using(var stream = new MemoryStream())
		{
			var writer = new BinaryWriter(stream);
			writer.Write("RIFF".ToCharArray());
			writer.Write((UInt32)0);             // chunk size
			writer.Write("WAVE".ToCharArray()); 
			writer.Write("fmt ".ToCharArray());
			writer.Write((UInt32)16);            // chunk size
			writer.Write((UInt16)1);             // audio format
			writer.Write((UInt16)channel);
			writer.Write((UInt32)rate);
			writer.Write((UInt32)(rate * channel * bps / 8)); // byte rate
			writer.Write((UInt16)(channel * bps / 8));               // block align
			writer.Write((UInt16)bps);
			writer.Write("data".ToCharArray());
			writer.Write((UInt32)(data.Length * channel * bps / 8));
			foreach (var elt in data) writer.Write(elt);
			writer.Seek(4, SeekOrigin.Begin);                     // seek to header chunk size field
			writer.Write((UInt32)(writer.BaseStream.Length - 8)); // chunk size
			stream.Seek(0, SeekOrigin.Begin);
			try
			{
				new SoundPlayer(stream).PlaySync();
			}
			catch(Exception)
			{
				_isstopped = true;
				Stop(stream);
			}
		}
	}
	
	private void Stop(MemoryStream stream)
	{
		if(stream != null && _isstopped == false)
		{
			_isstopped = true;
			stream.Dispose();
		}
		return;
	}
	
	public void CreateByteBeat(int rate, int timeline, byte[] data)
	{
		Load(1, rate, 8, timeline, data);
	}
}